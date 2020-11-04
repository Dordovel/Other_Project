#ifndef SFMLPROJECT_REBUILD_COLLISION_HPP
#define SFMLPROJECT_REBUILD_COLLISION_HPP

#include "../Interface/icollision.hpp"
#include "./physics.hpp"

namespace PROJECT::COLLISION
{
	class Collision final : public PROJECT::COLLISION::ICollision
	{
		private:

			PROJECT::PHYSICS::Physics _physics = {};

		public:
			std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
			    check_object_collision(const PROJECT::COLLECTION::ILayout* const lv,
			                            const INTERACTION* const rv ) noexcept override;

			std::pair<PROJECT::MOVE::Side, std::string>
			    check_object_collision(const INTERACTION* const lv,
			                            const INTERACTION* const rv) noexcept override;

	};
};
#endif //SFMLPROJECT_REBUILD_COLLISION_HPP
