#ifndef SFMLPROJECT_REBUILD_ANIMATED_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_ANIMATED_INTERFACE_HPP

#include "./animation.hpp"

namespace PROJECT
{
	namespace MOVE
	{
		enum class Side;
	};

	namespace ANIMATION
	{
		class IAnimated
		{
			public:

				virtual PROJECT::ANIMATION::IAnimation* get_animation_attack(PROJECT::MOVE::Side side) noexcept = 0;
				virtual PROJECT::ANIMATION::IAnimation* get_animation_walk(PROJECT::MOVE::Side side) noexcept = 0;
				virtual PROJECT::ANIMATION::IAnimation* get_animation_idle(PROJECT::MOVE::Side side) noexcept = 0;

				virtual ~IAnimated() = default;
		};
	};
};

#endif //SFMLPROJECT_REBUILD_ANIMATED_INTERFACE_HPP
