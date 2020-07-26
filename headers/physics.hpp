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

            bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const PROJECT::BASE::DATA::RectangleF& rv) noexcept override;

            bool check_intersection(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const std::shared_ptr<INTERACTION>& rv) noexcept override;

            bool check_intersection(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const PROJECT::BASE::DATA::RectangleF& rv) noexcept override;

            std::vector<std::string> get_intersection_object_name(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const std::shared_ptr<INTERACTION>& rv) noexcept override;

            std::vector<std::string> get_intersection_object_name(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const PROJECT::BASE::DATA::RectangleF& rv) noexcept override;

			Physics() = default;
			~Physics() = default;

	};

};
#endif //SFMLPROJECT_REBUILD_PHYSICS_HPP
