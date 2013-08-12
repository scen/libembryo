//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_size_h
#define libembryo_size_h

namespace embryo
{
    template<typename _T>
    class size
    {
    public:
        size<_T>() : m_w(0), m_h(0) {}
        
        size<_T>(_T w, _T h) : m_w(w), m_h(h) {}

        _T &h() { return m_h; }
        
        _T &w() { return m_w; }
    protected:
        _T m_w;
        _T m_h;
    };
    
    template<typename _T>
    size<_T> makesize(_T w, _T h)
    {
        return size<_T>(w, h);
    }
}

#endif