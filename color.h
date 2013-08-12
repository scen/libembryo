//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_color_h
#define libembryo_color_h

namespace embryo
{
    class color
    {
    public:
        color() : m_argb(0) {}
        color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) : m_r(r), m_g(g), m_b(b), m_a(a) {}

        static color &empty() { static color c = color(); return c; }
        static color &red() { static color c = color(255, 0, 0); return c; }
        static color &green() { static color c = color(0, 255, 0); return c; }
        static color &blue() { static color c = color(0, 0, 255); return c; }
        static color &black() { static color c = color(0, 0, 0); return c; }
        static color &white() { static color c = color(255, 255, 255); return c; }

        unsigned char r() const { return m_r; }
        unsigned char g() const { return m_g; }
        unsigned char b() const { return m_b; }
        unsigned char a() const { return m_a; }
        unsigned int argb() const { return m_argb; }
    protected:
        union
        {
            struct
            {
                unsigned char m_b;
                unsigned char m_g;
                unsigned char m_r;
                unsigned char m_a;
            };
            unsigned int m_argb;
        };
    };
}

#endif