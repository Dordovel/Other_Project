#ifndef SFMLPROJECT_REBUILD_OBJECT_SCALABLE_HPP
#define SFMLPROJECT_REBUILD_OBJECT_SCALABLE_HPP

namespace PROJECT::BASE::DATA
{
	class Vector2F;
};

class SCALABLE
{
	public:
		virtual void set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept = 0;
		virtual PROJECT::BASE::DATA::Vector2F get_scale() noexcept = 0;
		
		virtual ~SCALABLE() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_SCALABLE_HPP
