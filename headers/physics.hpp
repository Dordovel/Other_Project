#ifndef SFMLPROJECT_REBUILD_PHYSICS_HPP
#define SFMLPROJECT_REBUILD_PHYSICS_HPP

#include "../Interface/iphysics.hpp"
#include "../object/interaction.hpp"

namespace PROJECT::PHYSICS
{
	class Physics final : public PROJECT::PHYSICS::IPhysics
	{
		public:

			bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept override;

			std::vector<std::string> get_collision_object(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                          const std::shared_ptr<INTERACTION>& rv) noexcept override;

			Physics() = default;
			~Physics() = default;

			bool check_collision(const std::shared_ptr <PROJECT::COLLECTION::ICollection>& lv,
								 const std::shared_ptr <INTERACTION>& rv) noexcept override;
	};

};
#endif //SFMLPROJECT_REBUILD_PHYSICS_HPP
