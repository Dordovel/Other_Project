#ifndef SFMLPROJECT_REBUILD_MOUSE_UNIT_HPP
#define SFMLPROJECT_REBUILD_MOUSE_UNIT_HPP

#include "../Interface/imouse_unit.hpp"
#include <map>
#include "../struct/event_object.hpp"
#include <SFML/Window/Mouse.hpp>

namespace PROJECT::UNIT::CONTROL::MOUSE
{
    class MouseUnit : public PROJECT::UNIT::CONTROL::MOUSE::IMouseUnit
    {
        private:

            enum class _MouseEventType
            {
                Pressed,
                Released
            };

            struct _EventHandlerMousePressed
            {
                std::function<void(float X, float Y)> fun;
            };

            struct _EventHandlerMouseMoved
            {
                std::function<void(float X, float Y)> fun;
            };

            struct _EventHandlerMouseWheelScrolled
            {
                std::function<void(float X, float Y, float Delta)> fun;
            };

            struct _EventHandlerMouseEntered
            {
                std::function<void()> fun;
            };

            struct _EventHandlerMouseReleased
            {
                Mouse_Key::Button button;
                std::function<void()> fun;
            };

            std::map<Mouse_Key::Button, MouseUnit::_EventHandlerMousePressed> _eventMousePressedPool;

            std::vector<MouseUnit::_EventHandlerMouseMoved> _eventMouseMovedPool;
            std::vector<MouseUnit::_EventHandlerMouseWheelScrolled> _eventMouseWheelScrolledPool;
            std::vector<MouseUnit::_EventHandlerMouseEntered> _eventMouseEnteredPool;

            std::vector<MouseUnit::_EventHandlerMouseReleased> _eventMouseReleasedPool;

            inline void _catch_mouse_pressed_event(const PROJECT::EVENT::EventObject& event);
            inline void _catch_mouse_wheel_scrolled_event(const PROJECT::EVENT::EventObject& event);
            inline void _catch_mouse_mouse_moved_event(const PROJECT::EVENT::EventObject& event);
            inline void _catch_mouse_enter_event(const PROJECT::EVENT::EventObject& event);
            inline void _catch_mouse_released_event(const PROJECT::EVENT::EventObject& event);

            sf::Mouse _mouse;

        public:

            void entered(const std::function<void()>& fun) noexcept override;

            void button_pressed(int key, const std::function<void(int X, int Y)>& fun) noexcept override;

            void button_released(int key, const std::function<void()>& fun) noexcept override;

            void moved(const std::function<void(int X, int Y)>& fun) noexcept override;

            void wheel_scrolled(const std::function<void(int X, int Y, int Delta)>& fun) noexcept override;

            void catch_events(const PROJECT::EVENT::EventObject& event) override;

            BASE::DATA::Vector2I get_position_in_desktop() override;
    };
};
#endif //SFMLPROJECT_REBUILD_MOUSE_UNIT_HPP
