#ifndef SFMLPROJECT_REBUILD_DAMAGE_GENERATOR_HPP
#define SFMLPROJECT_REBUILD_DAMAGE_GENERATOR_HPP

#include <random>
#include <SFML/System/Time.hpp>
#include "../Interface/inpc.hpp"

namespace PROJECT::NPC
{
	class DamageGenerator
	{
		private:
			std::random_device _randDevice;
			std::mt19937 _mt;
			std::uniform_int_distribution<int> _uid;
			sf::Time _currentTime;
			sf::Time _frameTime;

		public:
			int generate(const std::shared_ptr<INpc>& person,
										const std::shared_ptr<INpc>& enemy,
										float delta) noexcept;

			void set_frame_time(float frameTime) noexcept;

			DamageGenerator();
			~DamageGenerator() = default;
	};
};

#endif //SFMLPROJECT_REBUILD_DAMAGE_GENERATOR_HPP
