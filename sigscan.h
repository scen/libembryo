//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_sigscan_h
#define libembryo_sigscan_h

#include <libembryo/signature.h>
#include <libembryo/module.h>

namespace embryo
{
    class sigscan
    {
    public:
        sigscan(signature &sig, module &mod);
        void *find();
    private:
        bool ran;
        void *result;
        signature m_sig;
        void *start;
        unsigned int size;
    };
}

#endif