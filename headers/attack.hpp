#pragma once

#include "../Interface/attack.hpp"
#include <random>
#include <SFML/System/Time.hpp>

namespace PROJECT::NPC
{
	class Attack : public PROJECT::NPC::IAttack
	{

		private:
			std::random_device _randDevice;
			std::mt19937 _mt;
			std::uniform_int_distribution<int> _uid;
			sf::Time _currentTime;
			sf::Time _frameTime;

		public:
			std::pair<int, int> attack(const std::shared_ptr<INpc>& person,
										const std::shared_ptr<INpc>& enemy,
										const bool personAttack, float delta) noexcept override;

			void set_param(float time) noexcept;

			Attack();
			~Attack() = default;
	};
};
