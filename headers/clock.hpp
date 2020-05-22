#pragma once
#include "../Interface/iclock.hpp"
#include <SFML/System/Clock.hpp>

    class Clock final : public IClock , public sf::Clock
{
    private:
        float _frametime;
        float _param;

    public:
        float get_time() const override;
        void restart() override;
        explicit Clock(float param);

		Clock() = default;
		~Clock() = default;
};
