#pragma once
#include "../Interface/icollision.hpp"
#include "../graphicobject/circle.hpp"
#include "./physics.hpp"

namespace PROJECT::COLLISION
{
	class Collision final : public PROJECT::COLLISION::ICollision
	{
		private:

			PROJECT::PHYSICS::Physics _physics = {};
			std::shared_ptr<DI> _circleRight;
			std::shared_ptr<DI> _circleLeft;
			std::shared_ptr<DI> _circleUp;
			std::shared_ptr<DI> _circleDown;


		public:
			std::pair<PROJECT::MOVE::Side, std::string> check_object_collision(const std::shared_ptr<PROJECT::COLLECTION::ILayout>& lv,
																				const std::shared_ptr<DI>& rv ) noexcept override;

			std::pair<PROJECT::MOVE::Side, std::string> check_object_collision(const std::shared_ptr<DI>& lv, const std::shared_ptr<DI>& rv) noexcept override;

			Collision();
			~Collision();
	};
};
