#ifndef libembryo_module_h
#define libembryo_module_h

#include <string>

namespace embryo
{
    class module
    {
    public:
        module(const std::string& name);

        void *start() { return m_start; }
        unsigned int size() { return m_size; }
    private:
        void *m_start;
        unsigned int m_size;
    };
}

#endif