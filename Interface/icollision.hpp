#ifndef SFMLPROJECT_REBUILD_COLLISION_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_COLLISION_INTERFACE_HPP

#include "./iphysics.hpp"
#include "./ilayout.hpp"

namespace PROJECT
{
	namespace MOVE
	{
		enum class Side;
	};

	namespace COLLISION
	{
		class ICollision
		{
			public:

				virtual std::pair<PROJECT::MOVE::Side, std::string>
				    check_object_collision(const INTERACTION* const lv,
				                            const INTERACTION* const rv) noexcept = 0;

				virtual std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
				    check_object_collision(const PROJECT::COLLECTION::ILayout* const lv,
				                           const INTERACTION* const rv ) noexcept = 0;
				
				virtual ~ICollision() = default;
		};
	};
};
#endif //SFMLPROJECT_REBUILD_COLLISION_INTERFACE_HPP
