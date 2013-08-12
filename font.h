//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_font_h
#define libembryo_font_h

#include <string>

namespace embryo
{
    class font
    {
    public:
        enum fontflags
        {
            none      = 0,
            bold      = 1 << 0,
            italic    = 1 << 1,
            underline = 1 << 2,
            center    = 1 << 3,
            vcenter   = 1 << 4,
            lalign    = 1 << 5,
            ralign    = 1 << 6,
            talign    = 1 << 7,
            balign    = 1 << 8,
            outline   = 1 << 9,
            strikeout = 1 << 11,
            dropshadow= 1 << 12,
            antialias = 1 << 13,
        };

        font(const std::string &name, unsigned int size) : m_name(name), m_size(size) {}
        font() {}

        unsigned int size() const { return m_size; }
        std::string name() const { return m_name; }
    protected:
        std::string m_name;
        unsigned int m_size;
    };
}

#endif