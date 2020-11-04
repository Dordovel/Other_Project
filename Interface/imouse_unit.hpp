#ifndef SFMLPROJECT_REBUILD_MOUSE_UNIT_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_MOUSE_UNIT_INTERFACE_HPP

#include "./icontrol_unit.hpp"

namespace PROJECT
{
    namespace BASE::DATA
    {
        class Vector2I;
    };

    namespace UNIT::CONTROL::MOUSE
    {
        class IMouseUnit : PROJECT::UNIT::CONTROL::IControlUnit
        {
            public:

                virtual void button_pressed(int key, std::function <void(int X, int Y)> fun) noexcept = 0;

                virtual void button_released(int key, std::function <void()> fun) noexcept = 0;

                virtual void moved(std::function <void(int X, int Y)> fun) noexcept = 0;

                virtual void
                wheel_scrolled(std::function <void(int X, int Y, int Delta)> fun) noexcept = 0;

                virtual void entered(std::function <void()> fun) noexcept = 0;

                virtual PROJECT::BASE::DATA::Vector2I get_position_in_desktop() = 0;

                virtual ~IMouseUnit() = default;

        };
    };
};
#endif //SFMLPROJECT_REBUILD_MOUSE_UNIT_INTERFACE_HPP
