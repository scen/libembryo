//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_render_h
#define libembryo_render_h

#include <libembryo/font.h>
#include <libembryo/color.h>
#include <libembryo/rect.h>
#include <libembryo/point.h>
#include <libembryo/size.h>

#include <boost/format.hpp>

#include <string>

using boost::format;

namespace embryo
{
    template<typename _T>
    class render
    {
    public:
        virtual size<_T> drawText(const point<_T> &p, const font &fnt, const color &col, const std::string &str) = 0;
        size<_T> drawText(const point<_T> &p, const font &fnt, const color &col, const format &fmt) { drawText(p, fnt, col, fmt.str()); }

        virtual size<_T> measureText(const font &fnt, const std::string &str) = 0;
        size<_T> measureText(const font &fnt, const format &fmt) { measureText(fnt, fmt.str()); }

        virtual void drawLine(const point<_T> &begin, const point<_T> &end, const color &col) = 0;

        virtual void fillRect(const rect<_T> &r, const color &col) = 0;
        virtual void outlineRect(const rect<_T> &r, const color &col) = 0;
    };
}

#endif