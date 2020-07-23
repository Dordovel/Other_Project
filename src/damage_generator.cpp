#include "../headers/damage_generator.hpp"
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

	int DamageGenerator::generate(int damage, float delta) noexcept
	{
		int result = 0;

		this->_currentTime += sf::milliseconds(delta);

		if (this->_currentTime >= this->_frameTime)
		{
			this->_currentTime = sf::microseconds(this->_currentTime.asMicroseconds() % this->_frameTime.asMicroseconds());

			this->_uid = std::uniform_int_distribution<int>(10, damage);
			result = this->_uid(this->_mt);
		}

		return result;
	}
};
