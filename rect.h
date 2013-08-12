//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_rect_h
#define libembryo_rect_h

#include <libembryo/point.h>
#include <libembryo/size.h>

namespace embryo
{
    template<typename _T>
    class rect
    {
    public:
        rect() : m_pos(), m_size() {}
        rect(const point<_T> &pt, const size<_T> &sz) : m_pos(pt), m_size(sz) {}

        point<_T> pos() const { return m_pos; }
        size<_T> size() const { return m_size; }
    protected:
        point<_T> m_pos;
        embryo::size<_T> m_size;
    };
    
    template<typename _T>
    rect<_T> makerect(point<_T> pos, size<_T> sz)
    {
        return rect<_T>(pos, sz);
    }
}

#endif