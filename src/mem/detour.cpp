//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#include "detour.h"

#include <libembryo/logger.h>
#include <libembryo/memmgr.h>

#include "distorm.h"
#include "mnemonics.h"
#include <AsmJit.h>

#include <mach/mach.h>

namespace embryo
{
    const unsigned int detour::JumpSize = 5;
    
    bool detour::apply()
    {
        if (m_applied) return false;
        
        kern_return_t err;
        unsigned int trampolineSize = detour::JumpSize * 4;
        m_trampoline = malloc(trampolineSize + 1);
        if (!m_trampoline)
        {
            log().error("failed to allocate trampoline");
            return 0;
        }
        memset(m_trampoline, 0, trampolineSize);
        
        err = vm_protect(mach_task_self(), (vm_address_t)m_trampoline, trampolineSize, 0, VM_PROT_READ | VM_PROT_EXECUTE | VM_PROT_WRITE);
        
        if (err)
        {
            log().error("failed to set trampoline to r/w/e");
            free(m_trampoline);
            return 0;
        }
        
        log().info(format("allocated trampoline @ %X") % m_trampoline);
        
        _DInst dec[1];
        unsigned int decCnt = 0;
        
        _CodeInfo ci = {0};
        ci.code = (unsigned char *)m_src;
        ci.codeOffset = (_OffsetType)m_src;
        ci.codeLen = 64;
        ci.dt = Decode32Bits;
        ci.features = DF_NONE;
        
        unsigned char *curTrampolinePtr = (unsigned char *)m_trampoline;
        
        unsigned int instructionsSize = 0;
        
        log().info("start copying/disasm instructions");
        
        // copy instructions to trampoline until we have enough room for a JMP
        do {
            distorm_decompose64(&ci, dec, 1, &decCnt);
            if (dec->flags == FLAG_NOT_DECODABLE)
            {
                log().error(format("disasm resulted in FLAG_NOT_DECODABLE. address: %X") % ci.codeOffset);
                return false;
            }
            
            _DecodedInst res = {0};
            distorm_format64(&ci, dec, &res);
            log().verb(format("%08llx (%02d) %-20s %s%s%s") % res.offset % res.size % res.instructionHex.p % res.mnemonic.p
                       % (res.operands.length != 0 ? " " : "") % res.operands.p);
            
            // TODO: check for more branching instructions
            if (META_GET_FC(dec->meta) == FC_UNC_BRANCH || META_GET_FC(dec->meta) == FC_CND_BRANCH)
            {
                if (dec->opcode == I_JMP)
                {
                    if (dec->ops[0].type == O_PC)
                    {
                        log().info("relocating JMP");
                        // INSTRUCTION_GET_TARGET(m) will return the absolute address
                        // imm.addr is relative offset
                        makeJmp(curTrampolinePtr, (void *)dec->imm.addr);
                        curTrampolinePtr += dec->size;
                    }
                    else
                    {
                        log().error("unknown JMP opcode");
                        return 0;
                    }
                }
                else
                {
                    log().error(format("no implementation for branch: %s") % GET_MNEMONIC_NAME(dec->opcode));
                    return 0;
                }
            }
            else
            {
                // non-branching instruction
                memcpy(curTrampolinePtr, (void *)ci.codeOffset, dec->size);
                curTrampolinePtr += dec->size;
            }
            ci.codeOffset = ci.nextOffset;
            ci.code += dec->size;
            instructionsSize += dec->size;
        } while (instructionsSize < detour::JumpSize);
        
        log().info(format("copied %d bytes") % instructionsSize);
        
        // jump from trampoline back to the source
        makeJmp(curTrampolinePtr, (unsigned char *)m_src + instructionsSize);
        
        vm_prot_t origProt;
        err = memmgr::getMemoryProtection(m_src, origProt);
        
        if (err)
        {
            log().error("getMemoryProtection failed");
            return 0;
        }
        
        err = vm_protect(mach_task_self(), (vm_address_t)m_src, detour::JumpSize, 0, VM_PROT_EXECUTE | VM_PROT_READ | VM_PROT_WRITE);
        
        if (err)
        {
            log().error(format("vm_protect() failed to set r/w/e"));
            return 0;
        }
        
        // back up instructions for restoring
        m_orig_bytes = memmgr::readBytes(m_src, instructionsSize);
        
        makeJmp(m_src, m_dst);
        m_applied = true;
        
        // restore original protection
        vm_protect(mach_task_self(), (vm_address_t)m_src, detour::JumpSize, 0, origProt);
        
        return true;
    }
    
    void detour::makeJmp(void *addr, void *target)
    {
        AsmJit::Assembler jit;
        jit.jmp(target);
        sysint_t stubSize = jit.getCodeSize();
        
        if (stubSize != detour::JumpSize)
        {
            log().error(format("stubSize (%d) != JumpSize (%d)") % stubSize % detour::JumpSize);
            return;
        }
        
        std::vector<unsigned char> jmpBuf(stubSize);
        jit.relocCode(jmpBuf.data(), (sysuint_t)addr);
        memmgr::writeBytes(addr, jmpBuf);
    }
    
    void detour::remove()
    {
        if (!m_applied) return;
        memmgr::writeBytes(m_src, m_orig_bytes);
        m_applied = false;
    }
}