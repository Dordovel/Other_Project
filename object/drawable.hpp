#ifndef SFMLPROJECT_REBUILD_OBJECT_DRAWABLE_HPP
#define SFMLPROJECT_REBUILD_OBJECT_DRAWABLE_HPP

#include <string>

namespace PROJECT::BASE::DATA
{
    class DrawableObject;
};

class DRAWABLE
{
    public:
        virtual PROJECT::BASE::DATA::DrawableObject draw() const noexcept = 0;
        virtual void visible(bool flag) noexcept = 0;
        virtual bool is_visible() noexcept = 0;
		
		virtual ~DRAWABLE() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_DRAWABLE_HPP
