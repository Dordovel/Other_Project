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
				    check_object_collision(const std::shared_ptr<INTERACTION>& lv,
				                            const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

				virtual std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
				    check_object_collision(const std::shared_ptr<PROJECT::COLLECTION::ILayout>& lv,
				                           const std::shared_ptr<INTERACTION>& rv ) noexcept = 0;
				
				virtual ~ICollision() = default;
		};
	};
};
#endif //SFMLPROJECT_REBUILD_COLLISION_INTERFACE_HPP
