#ifndef SFMLPROJECT_REBUILD_DAMAGE_GENERATOR_HPP
#define SFMLPROJECT_REBUILD_DAMAGE_GENERATOR_HPP

#include <random>
#include <SFML/System/Time.hpp>
#include "../Interface/istate.hpp"

namespace PROJECT::NPC
{
	class DamageGenerator
	{
		private:
			std::random_device _randDevice;
			std::mt19937 _mt;
			std::uniform_real_distribution<float> _uid;
			sf::Time _currentTime;
			sf::Time _frameTime;

		public:
			float generate(const PROJECT::NPC::INpcState* const npc, float delta) noexcept;

			void set_frame_time(float frameTime) noexcept;

			DamageGenerator();
			~DamageGenerator() = default;
	};
};

#endif //SFMLPROJECT_REBUILD_DAMAGE_GENERATOR_HPP
