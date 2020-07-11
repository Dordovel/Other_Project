#include "headers/damage_generator.hpp"
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

	int DamageGenerator::generate(const std::shared_ptr<INpc>& person,
										const std::shared_ptr<INpc>& enemy,
										float delta) noexcept
	{
		int result = -1;

		this->_currentTime += sf::milliseconds(delta);

		if (this->_currentTime >= this->_frameTime)
		{
			this->_currentTime = sf::microseconds(this->_currentTime.asMicroseconds() % this->_frameTime.asMicroseconds());

			this->_uid = std::uniform_int_distribution<int>(10, person->get_damage());
			result = this->_uid(this->_mt);
			enemy->set_health(enemy->get_health() - result);
		}

		return result;
	}
};
