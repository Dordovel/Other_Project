#include "../headers/generatdamage.hpp"
#include <random>

namespace PROJECT::NPC
{

	DamageGenerator::DamageGenerator()
	{
		this->_mt = std::mt19937(this->_randDevice());
	}

	
	void DamageGenerator::set_frame_time(float frameTime) noexcept
	{
		this->_frameTime = sf::seconds(frameTime);
	}

	std::pair<int, int> DamageGenerator::generate(const std::shared_ptr<INpc>& person,
										const std::shared_ptr<INpc>& enemy,
										const bool personAttack, float delta) noexcept
	{	
		std::pair attack(-1, -1);

		this->_currentTime += sf::milliseconds(delta);

		if (this->_currentTime >= this->_frameTime)
		{
			this->_currentTime = sf::microseconds(this->_currentTime.asMicroseconds() % this->_frameTime.asMicroseconds());

			if(personAttack)
			{
				this->_uid = std::uniform_int_distribution<int>(0, person->get_damage());
				attack.first = this->_uid(this->_mt);
				enemy->set_health(enemy->get_health() - attack.first);
			}

			this->_uid = std::uniform_int_distribution<int>(0, enemy->get_damage());
			attack.second = this->_uid(this->_mt);
			person->set_health(person->get_health() - attack.second);
		}

		return attack;
	}
};
