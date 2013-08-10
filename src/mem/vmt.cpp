//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#include "vmt.h"

#include <libembryo/logger.h>
#include <libembryo/memmgr.h>

#include <cstdlib>

#include <mach/mach.h>

namespace embryo
{
	unsigned int vmt::countFuncs(void **vmt)
	{
		int cnt = -1;
        vm_prot_t prot;
        do {
            cnt++;
            
        	kern_return_t status = memmgr::getMemoryProtection(vmt[cnt], prot);
        	if (status)
        	{
        		log().error("vm_region() failed");
        		break;
        	}
        } while (((prot & VM_PROT_EXECUTE) && (prot & VM_PROT_READ)) || // read/exec
                 ((prot & VM_PROT_READ) && (prot & VM_PROT_EXECUTE) && (prot & VM_PROT_WRITE))); // read/write/exec
        
        log().info(format("vfunc count: %d") % cnt);
		return cnt;
	}
    
	int vmt::findFunc(void **vmt, void *func, unsigned int vfuncs)
	{
		if (!vfuncs) vfuncs = countFuncs(vmt);
		for (unsigned int i = 0; i < vfuncs; i++)
		{
			if (vmt[i] == func) return i;
		}
		return -1;
	}
    
	vmt::vmt(void *inst, size_t offset, unsigned int vfuncs)
	{
		vftable = makeptr<void **>(inst, offset);
		oldvmt = *vftable;
		if (!vfuncs) vfuncs = countFuncs(oldvmt);
		vcount = vfuncs;
		array = (void **)malloc((vfuncs + 3) * sizeof(void *));
		array[2] = oldvmt[-1];
		for (unsigned int i = 0; i < vfuncs; ++i) array[i + 3] = oldvmt[i];
		*vftable = array + 3;
	}
	vmt::~vmt()
	{
		if (vftable) unhook();
		free(array);
	}
}