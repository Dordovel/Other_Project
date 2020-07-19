#ifndef SFMLPROJECT_REBUILD_KEYBOARD_UNIT_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_KEYBOARD_UNIT_INTERFACE_HPP

#include "./icontrol_unit.hpp"

namespace PROJECT::UNIT::CONTROL::KEYBOARD
{
    class IKeyboardUnit : public PROJECT::UNIT::CONTROL::IControlUnit
    {
        public:
            virtual void set_close_window_event(const std::function <void()> &closeWindowEvent) noexcept = 0;

            virtual void button_pressed(int key, const std::function <void()> &fun,
                                           PROJECT::UNIT::CONTROL::EventHandlerType eventType) noexcept = 0;

            virtual void button_released(int key, const std::function <void()> &fun) noexcept = 0;

            virtual void catch_events() = 0;

            virtual ~IKeyboardUnit() = default;
    };
};

#endif //SFMLPROJECT_REBUILD_KEYBOARD_UNIT_INTERFACE_HPP
