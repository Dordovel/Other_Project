#include "../headers/clock.hpp"

float Clock::get_time() const
{
    return this->_frametime;
}

void Clock::restart()
{
    this->_frametime = sf::Clock::getElapsedTime().asMicroseconds() / this->_param;
    sf::Clock::restart();
}

Clock::Clock(float param):_param(param),
                            _frametime(0)
{}
