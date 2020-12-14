#ifndef SFMLPROJECT_REBUILD_OBJECT_ANIMATED_HPP
#define SFMLPROJECT_REBUILD_OBJECT_ANIMATED_HPP

namespace PROJECT::BASE::DATA
{
	class RectangleI;
};

class TEXTURED
{
	public:
		virtual void set_texture_rect(PROJECT::BASE::DATA::RectangleI rect) = 0;

		virtual ~TEXTURED() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_ANIMATED_HPP
