#ifndef SFMLPROJECT_REBUILD_OBJECT_STATIC_HPP
#define SFMLPROJECT_REBUILD_OBJECT_STATIC_HPP

namespace PROJECT::BASE::DATA
{
	class RectangleF;
	class Vector2F;
};

class STATIC
{
    public:
		virtual PROJECT::BASE::DATA::RectangleF get_global_bounds() const noexcept = 0;

        virtual PROJECT::BASE::DATA::Vector2F get_position() const noexcept = 0;

        virtual ~STATIC() = default;
};

#endif //SFMLPROJECT_REBUILD_OBJECT_STATIC_HPP
