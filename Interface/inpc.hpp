#pragma once 

#include "./iarmor.hpp"
#include "./ipoints.hpp"
#include "./ihealth.hpp"
#include "./idamage.hpp"
#include "./animation.hpp"

namespace PROJECT::MOVE
{
	enum class Side;
}

namespace PROJECT::NPC
{
	class INpc : public IDamage,
				public IHealth,
				public IPoints,
				public IArmor
	{
		public:

			virtual PROJECT::ANIMATION::IAnimation& get_animation_attack(PROJECT::MOVE::Side side) noexcept = 0;
			virtual PROJECT::ANIMATION::IAnimation& get_animation_walk(PROJECT::MOVE::Side side) noexcept = 0;
			virtual ~INpc() = default;
	};
};
