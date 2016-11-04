//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#include "sigscan.h"

namespace embryo
{
    sigscan::sigscan(signature sig, module& mod) : m_sig(sig),
        start(mod.start()), size(mod.size()), result(NULL), ran(false)
    {
    }
    
    sigscan::sigscan(signature sig, void *start, unsigned int size) : m_sig(sig),
        start(start), size(size)
    {
    }

    void *sigscan::find()
    {
        if (ran) return result;

        for (uint64_t i = (uint64_t)start; i < (uint64_t)start + size; i++)
        {
            bool flag = true;
            for (int j = 0; j < m_sig.mask().length(); j++)
            {
                if (m_sig.mask()[j] == 'x' && 
                    *(unsigned char *)(i + j) != (unsigned char)m_sig.pattern()[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return result = (void *)i;
        }
        return result = NULL;
    }
};
