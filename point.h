//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_point_h
#define libembryo_point_h

namespace embryo
{
    template<typename _T>
    class point
    {
    public:
        point() : m_x(0), m_y(0) {}
        point(int x, int y) : m_x(x), m_y(y) {}

        _T x() const { return m_x; }
        _T y() const { return m_y; }

        void setX(_T x) { m_x = x; }
        void setY(_T y) { m_y = y; }
    protected:
        _T m_x;
        _T m_y;
    };
    
    template<typename _T>
    point<_T> makepoint(_T x, _T y)
    {
        return point<_T>(x, y);
    }
}

#endif