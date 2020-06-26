#pragma once
#include "../Interface/iphysics.hpp"
#include "../object/interaction.hpp"

namespace PROJECT::PHYSICS
{
	class Physics final : public PROJECT::PHYSICS::IPhysics
	{
		public:

			bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept override;

			std::string check_collision(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
									const std::shared_ptr<INTERACTION>& rv) noexcept override;

			Physics() = default;
			~Physics() = default;
	};
};