#include "sigscan.h"

namespace embryo
{
    sigscan::sigscan(signature& sig, module& mod) : m_sig(sig),
        start(mod.start()), size(mod.size()), result(NULL), ran(false)
    {
    }

    void *sigscan::find()
    {
        if (ran) return result;

        for (unsigned int i = (unsigned int)start; i < (unsigned int)start + size; i++)
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