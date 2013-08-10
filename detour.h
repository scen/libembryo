//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_detour_h
#define libembryo_detour_h

#include <vector>

namespace embryo
{
    class detour
    {
    public:
        detour(void *src, void *dst) : m_src(src), m_dst(dst), m_applied(false), m_trampoline(0) {}
        
        bool apply();
        void remove();
        template<typename Fn>
        Fn trampoline() const { return (Fn)m_trampoline; }
        
        const static unsigned int JumpSize;
    protected:
        void makeJmp(void *addr, void *target);
    private:
        void *m_src;
        void *m_dst;
        void *m_trampoline;
        bool m_applied;
        std::vector<unsigned char> m_orig_bytes;
    };
}

#endif