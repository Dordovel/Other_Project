#pragma once

#include "./inpc.hpp"
#include <memory>

namespace PROJECT::NPC
{
	class IAttack
	{
		public:
			 virtual std::pair<int, int> attack(const std::shared_ptr<INpc>& person, 
												const std::shared_ptr<INpc>& enemy, 
												const bool personAttack, float delta) noexcept = 0;
			virtual ~IAttack() = default;

	};
}
