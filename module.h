//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_module_h
#define libembryo_module_h

#include <string>

#include <sys/types.h>
#include <mach/error.h>
#include <mach/vm_types.h>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>
#include <mach/mach.h>
#include <sys/stat.h>
#include <dlfcn.h>

namespace embryo
{
    class module
    {
    public:
        module(const std::string &name);

        void *start() const { return m_start; }
        unsigned int size() const { return m_size; }
        std::string name() const { return m_name; }
        std::string path() const { return m_path; }
        mach_header *machHeader() const { return m_header; }
        void *handle() const { return m_handle; }
        template<typename Fn>
        Fn getSymbol(const char *name) const
        {
            return (Fn)dlsym(handle(), name);
        }
    private:
        void *m_start;
        unsigned int m_size;
        std::string m_name;
        std::string m_path;
        mach_header *m_header;
        void *m_handle;
    };
}

#endif