#ifndef libembryo_memmgr_h
#define libembryo_memmgr_h

#include <vector>

#include <mach/mach.h>

namespace embryo
{
    class memmgr
    {
    public:
        static kern_return_t getMemoryProtection(void *addr, vm_prot_t &prot);
        static bool writeBytes(void *dst, std::vector<unsigned char>& bytes);
        static std::vector<unsigned char> readBytes(void *src, int len);
    };
}

#endif