#include "../headers/keyboard_unit.hpp"
#include "../struct/event_object.hpp"

namespace PROJECT::UNIT::CONTROL::KEYBOARD
{
    void KeyboardUnit::set_close_window_event(const std::function<void()>& closeWindowEvent) noexcept
    {
        this->_closeWindowEvent = closeWindowEvent;
    }

    void KeyboardUnit::button_pressed(int key , const std::function<void()>& fun , EventHandlerType eventType) noexcept
    {
        KeyboardUnit::EventHandler eventHandler;
        eventHandler.key = static_cast<Keyboard_Key::Key>(key);
        eventHandler.fun = fun;
        eventHandler.type = KeyboardUnit::KeyEventType::Pressed;

        if (eventType == EventHandlerType::EVENT_LOOP)
        {
            this->_keyPressedEventLoop.push_back(eventHandler);
        }
        else if(eventType == EventHandlerType::NONE)
        {
            this->_keyPressedEventNone.push_back(eventHandler);
        }
    }

    void KeyboardUnit::button_released(int key , const std::function<void()>& fun) noexcept
    {
        KeyboardUnit::EventHandler eventHandler;
        eventHandler.key = static_cast<Keyboard_Key::Key>(key);
        eventHandler.fun = fun;
        eventHandler.type = KeyboardUnit::KeyEventType::Released;

        this->_keyPressedEventLoop.push_back(eventHandler);
    }

    void KeyboardUnit::catch_events()
    {
        for (const KeyboardUnit::EventHandler& eventHandlerNone : this->_keyPressedEventNone)
        {
            if(Keyboard_Key::isKeyPressed(eventHandlerNone.key))
            {
                eventHandlerNone.fun();
            }
        }
    }


    void KeyboardUnit::catch_events(const PROJECT::EVENT::EventObject& event)
    {
        if(event.type == PROJECT::EVENT::EventObject::Closed)
        {
            this->_closeWindowEvent();
        }

        for(const KeyboardUnit::EventHandler& eventHandlerLoop : this->_keyPressedEventLoop)
        {
            if( eventHandlerLoop.type == KeyboardUnit::KeyEventType::Pressed)
            {
                if((event.type == PROJECT::EVENT::EventObject::KeyPressed) && (event.key.code == eventHandlerLoop.key))
                {
                    eventHandlerLoop.fun();
                }
            }
            else
            {
                if((event.type == PROJECT::EVENT::EventObject::KeyReleased) && (event.key.code == eventHandlerLoop.key))
                {
                    eventHandlerLoop.fun();
                }
            }
        }
    }
};
