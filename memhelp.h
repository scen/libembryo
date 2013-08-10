//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_memhelp_h
#define libembryo_memhelp_h

#include "stddef.h"

namespace embryo
{
    inline void **&getvtable(void *inst, size_t offset =0)
    {
        return *reinterpret_cast<void ***>((size_t)inst + offset);
    }
    
    inline const void **getvtable(const void *inst, size_t offset = 0)
    {
        return *reinterpret_cast<const void ***>((size_t)inst + offset);
    }
    
    template<typename Fn>
    inline Fn getvfunc(const void *inst, size_t index, size_t offset = 0)
    {
        return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
    }
    
    template<typename T> inline T *makeptr(void *ptr, int offset)
    {
        return reinterpret_cast<T *>((size_t)ptr + offset);
    }
    
    template<typename T> inline T *makeptr(unsigned int ptr, int offset)
    {
        return reinterpret_cast<T *>((size_t)ptr + offset);
    }
}

#endif