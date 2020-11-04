#ifndef SFMLPROJECT_REBUILD_PHYSICS_HPP
#define SFMLPROJECT_REBUILD_PHYSICS_HPP

#include "../Interface/iphysics.hpp"
#include "../object/interaction.hpp"

namespace PROJECT::PHYSICS
{
	class Physics final : public PROJECT::PHYSICS::IPhysics
	{
		public:

            bool check_intersection(const INTERACTION* const lv, const INTERACTION* const rv) noexcept override;

            bool check_intersection(const INTERACTION* const lv, PROJECT::BASE::DATA::RectangleF rv) noexcept override;

            bool check_intersection(const INTERACTION* const lv, PROJECT::BASE::DATA::Vector2F rv) noexcept override;

            bool check_intersection(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  const INTERACTION* const rv) noexcept override;

            bool check_intersection(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  PROJECT::BASE::DATA::RectangleF rv) noexcept override;

            std::vector<std::string> get_intersection_object_name(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  const INTERACTION* const rv) noexcept override;

            std::vector<std::string> get_intersection_object_name(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  PROJECT::BASE::DATA::RectangleF rv) noexcept override;

			Physics() = default;
			~Physics() = default;

	};

};
#endif //SFMLPROJECT_REBUILD_PHYSICS_HPP
