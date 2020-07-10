#ifndef SFMLPROJECT_REBUILD_SIDE_GENERATOR_HPP
#define SFMLPROJECT_REBUILD_SIDE_GENERATOR_HPP

#include "../struct/side.hpp"
#include <SFML/System/Time.hpp>

namespace PROJECT::NPC
{
	class SideGenerator
	{
		private:
			sf::Time _currentTime;
			sf::Time _frameTime;
			PROJECT::MOVE::Side _lastSide;
			
			PROJECT::MOVE::Side generate_rand_side() noexcept;

		public:
			PROJECT::MOVE::Side generate(float delta) noexcept;
			void set_frame_time(float frameTime) noexcept;
			SideGenerator(float frameTime);
			~SideGenerator() = default;	
	};
};
#endif //SFMLPROJECT_REBUILD_SIDE_GENERATOR_HPP
