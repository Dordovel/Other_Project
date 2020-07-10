#ifndef SFMLPROJECT_REBUILD_POINTS_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_POINTS_INTERFACE_HPP

namespace PROJECT::NPC
{
	class IPoints
	{
		public:
			virtual int get_points() const noexcept = 0;
			virtual void set_points(int points) noexcept = 0;
	};
};
#endif //SFMLPROJECT_REBUILD_POINTS_INTERFACE_HPP
