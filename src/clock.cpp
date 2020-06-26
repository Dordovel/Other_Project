#include "../headers/clock.hpp"
#include <iostream>

namespace PROJECT::CLOCK
{
    unsigned int Clock::get_elapsed_time() const noexcept
    {
        return this->_clock.getElapsedTime().asMilliseconds();
    }

    unsigned int Clock::get_work_time() const noexcept
    {
        return this->_workTime.asMilliseconds();
    }

    void Clock::restart() noexcept
    {
        this->_workTime = this->_clock.restart();
    }
};
