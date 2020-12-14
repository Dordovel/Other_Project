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

	float DamageGenerator::generate(const PROJECT::NPC::INpcState* const npc, float delta) noexcept
	{
		float result = 0.f;

		this->_currentTime += sf::milliseconds(delta);

		if (this->_currentTime >= this->_frameTime)
		{
			this->_currentTime = sf::microseconds(this->_currentTime.asMicroseconds() % this->_frameTime.asMicroseconds());

			this->_uid = std::uniform_real_distribution<float>(10.f, npc->get_damage());
			result = this->_uid(this->_mt);
		}

		return result;
	}
};
