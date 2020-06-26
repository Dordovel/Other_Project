#pragma once 
#include "./iphysics.hpp"
#include "./ilayout.hpp"
#include "../object/di.hpp"

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

				virtual std::pair<PROJECT::MOVE::Side, std::string> check_object_collision(const std::shared_ptr<DI>& lv, const std::shared_ptr<DI>& rv) noexcept = 0;
				virtual std::pair<PROJECT::MOVE::Side, std::string> check_object_collision(const std::shared_ptr<PROJECT::COLLECTION::ILayout>& lv,
																					const std::shared_ptr<DI>& rv ) noexcept = 0;
				
				virtual ~ICollision() = default;
		};
	};
};
