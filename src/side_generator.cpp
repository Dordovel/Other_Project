#include "headers/side_generator.hpp"
#include <random>

namespace PROJECT::NPC
{

	SideGenerator::SideGenerator(float frameTime)
	{
		this->set_frame_time(frameTime);
	}

	PROJECT::MOVE::Side SideGenerator::generate(float delta) noexcept
	{
		this->_currentTime += sf::milliseconds(delta);

		if (this->_currentTime >= this->_frameTime)
		{
			this->_currentTime = sf::microseconds(this->_currentTime.asMicroseconds() % this->_frameTime.asMicroseconds());
			
			this->_lastSide = generate_rand_side();
		}

		return this->_lastSide;
	}

	PROJECT::MOVE::Side SideGenerator::generate_rand_side() noexcept
	{
			std::random_device rand_device;
			std::mt19937 mt(rand_device());
			std::uniform_int_distribution<int> uid (1, 10);

			int number = uid(mt);

			switch(number)
			{
				case 2:
					return PROJECT::MOVE::Side::DOWN;
				case 4:
					return PROJECT::MOVE::Side::RIGHT;
				case 6:
					return PROJECT::MOVE::Side::LEFT;
				case 8:
					return PROJECT::MOVE::Side::UP;
			}

			return PROJECT::MOVE::Side::NONE;
	}


	void SideGenerator::set_frame_time(float frameTime) noexcept
	{
		this->_frameTime = sf::seconds(frameTime);
	}
};
