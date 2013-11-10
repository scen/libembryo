//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

namespace embryo
{
    class window : public drawable
    {
    public:
        window() : window(rect()) {} 
        window(rect &r) : window(r.pos(), r.size()) {}
        window(point &p, size &sz) : m_pt(p), m_sz(sz) {} 
    private:
        point m_pt;
        size m_sz;
    };
}