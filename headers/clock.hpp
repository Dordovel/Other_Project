#ifndef SFMLPROJECT_REBUILD_CLOCK_HPP
#define SFMLPROJECT_REBUILD_CLOCK_HPP

#include "../Interface/iclock.hpp"
#include <SFML/System/Clock.hpp>

namespace PROJECT::CLOCK
{
	class Clock final : public PROJECT::CLOCK::IClock 
	{
		private:
			sf::Clock _clock = {};
			sf::Time _workTime = {};

		public:
			unsigned int get_elapsed_time() const noexcept override;
			unsigned int get_work_time() const noexcept override;
			void restart() noexcept override;

			Clock() = default;
			~Clock() = default;
	};
};

#endif //SFMLPROJECT_REBUILD_CLOCK_HPP