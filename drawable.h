//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#include <list>
#include <memory>

namespace embryo
{
    class drawable
    {
    public:
        virtual void calculate() = 0;
        virtual void draw() = 0;
        virtual bool onMouseDown() = 0;
        virtual bool onHover() = 0;
        virtual bool onMouseUp() = 0;
        std::list<std::shared_ptr<drawable>> children() const { return m_children; }
    protected:
        std::list<std::shared_ptr<drawable>> m_children;
    };
}