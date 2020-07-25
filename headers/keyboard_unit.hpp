#ifndef SFMLPROJECT_REBUILD_KEYBOARD_UNIT_HPP
#define SFMLPROJECT_REBUILD_KEYBOARD_UNIT_HPP

#include<vector>
#include <map>
#include "../Interface/ikeyboard_unit.hpp"
#include "../struct/event_object.hpp"

namespace PROJECT::UNIT::CONTROL::KEYBOARD
{
    class KeyboardUnit final : public PROJECT::UNIT::CONTROL::KEYBOARD::IKeyboardUnit
    {
        private:

            enum class _KeyEventType
            {
                Pressed,
                Released
            };

            struct _EventHandler
            {
                Keyboard_Key::Key key;
                std::function<void()> fun;
                KeyboardUnit::_KeyEventType type;
            };

            std::function<void()> _closeWindowEvent;

            std::vector<KeyboardUnit::_EventHandler> _keyPressedEventLoop;
            std::vector<KeyboardUnit::_EventHandler> _keyPressedEventNone;

        public:
            void set_close_window_event(const std::function<void()>& closeWindowEvent) noexcept override;
            
            void button_pressed(int key , const std::function<void()>& fun , EventHandlerType eventType) noexcept override;
            
            void button_released(int key , const std::function<void()>& fun) noexcept override;

            void catch_events() override;

            void catch_events(const PROJECT::EVENT::EventObject& event) override;

            ~KeyboardUnit() = default;

            KeyboardUnit() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_KEYBOARD_UNIT_HPP
