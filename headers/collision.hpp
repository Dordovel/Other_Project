#pragma once
#include "../Interface/icollision.hpp"
#include "./physics.hpp"
#include "../object/object.hpp"

namespace PROJECT::COLLISION
{
	class Collision final : public PROJECT::COLLISION::ICollision
	{
		private:

			PROJECT::PHYSICS::Physics _physics = {};
			std::shared_ptr<OBJECT> _circleRight;
			std::shared_ptr<OBJECT> _circleLeft;
			std::shared_ptr<OBJECT> _circleUp;
			std::shared_ptr<OBJECT> _circleDown;


		public:
			std::pair<PROJECT::MOVE::Side, std::string> check_object_collision(const std::shared_ptr<PROJECT::COLLECTION::ILayout>& lv,
																				const std::shared_ptr<INTERACTION>& rv ) noexcept override;

			std::pair<PROJECT::MOVE::Side, std::string> check_object_collision(const std::shared_ptr<INTERACTION>& lv,
																				const std::shared_ptr<INTERACTION>& rv) noexcept override;

			Collision(std::shared_ptr<OBJECT>&& rail);
			~Collision();
	};
};
