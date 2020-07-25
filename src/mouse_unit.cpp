#include "../headers/mouse_unit.hpp"
#include "../struct/vector_object.hpp"

namespace PROJECT::UNIT::CONTROL::MOUSE
{
    void MouseUnit::_catch_mouse_wheel_scrolled_event(const PROJECT::EVENT::EventObject& event)
    {
        if ( event.type == sf::Event::MouseWheelScrolled )
        {
            for ( const auto& value : this->_eventMouseWheelScrolledPool )
            {
                value.fun(event.mouseWheelScroll.x, event.mouseWheelScroll.y,
                          event.mouseWheelScroll.delta);
            }
        }
    }

    void MouseUnit::_catch_mouse_mouse_moved_event(const PROJECT::EVENT::EventObject& event)
    {
        if ( event.type == sf::Event::MouseMoved )
        {
            for ( const auto& value : this->_eventMouseMovedPool )
            {
                value.fun(event.mouseMove.x, event.mouseMove.y);
            }
        }
    }

    void MouseUnit::_catch_mouse_enter_event(const PROJECT::EVENT::EventObject& event)
    {
        if ( event.type == sf::Event::MouseEntered )
        {
            for ( const auto& value : this->_eventMouseEnteredPool )
            {
                value.fun();
            }
        }
    }

    void MouseUnit::_catch_mouse_pressed_event(const PROJECT::EVENT::EventObject& event)
    {
        if ( event.type == sf::Event::MouseButtonPressed )
        {
            auto value = this->_eventMousePressedPool.find(event.mouseButton.button);

            if ( value != this->_eventMousePressedPool.end())
            {
                value->second.fun(( event.mouseButton.x - 10 ), ( event.mouseButton.y - 10 ));
            }
        }
    }

    void MouseUnit::_catch_mouse_released_event(const PROJECT::EVENT::EventObject& event)
    {
        if ( event.type == sf::Event::MouseButtonReleased )
        {
            for ( const auto& value : this->_eventMouseReleasedPool )
            {
                if(!_mouse.isButtonPressed(value.button))
				{
					value.fun();
				}
            }
        }
    }

    void MouseUnit::button_pressed(int key, const std::function <void(int X, int Y)>& fun) noexcept
    {
        MouseUnit::_EventHandlerMousePressed eventHandler;
        eventHandler.fun = fun;
        auto value = static_cast<Mouse_Key::Button>(key);

        this->_eventMousePressedPool.emplace(value, eventHandler);
    }

    void MouseUnit::moved(const std::function <void(int X, int Y)>& fun) noexcept
    {
        MouseUnit::_EventHandlerMouseMoved eventHandler;
        eventHandler.fun = fun;

        this->_eventMouseMovedPool.push_back(eventHandler);
    }

    void MouseUnit::wheel_scrolled(const std::function <void(int X, int Y, int Delta)>& fun) noexcept
    {
        MouseUnit::_EventHandlerMouseWheelScrolled eventHandler;
        eventHandler.fun = fun;

        this->_eventMouseWheelScrolledPool.push_back(eventHandler);
    }

    void MouseUnit::entered(const std::function <void()>& fun) noexcept
    {
        MouseUnit::_EventHandlerMouseEntered eventHandler;
        eventHandler.fun = fun;

        this->_eventMouseEnteredPool.push_back(eventHandler);
    }

    void MouseUnit::button_released(int key, const std::function <void()>& fun) noexcept
    {
        MouseUnit::_EventHandlerMouseReleased eventHandler;
        eventHandler.fun = fun;
        eventHandler.button = static_cast<Mouse_Key::Button>(key);

        this->_eventMouseReleasedPool.push_back(eventHandler);
    }

    void MouseUnit::catch_events(const PROJECT::EVENT::EventObject& event)
    {
        this->_catch_mouse_enter_event(event);
        this->_catch_mouse_mouse_moved_event(event);
        this->_catch_mouse_pressed_event(event);
        this->_catch_mouse_released_event(event);
        this->_catch_mouse_wheel_scrolled_event(event);
    }

    BASE::DATA::Vector2I MouseUnit::get_position_in_desktop()
    {
        return this->_mouse.getPosition() - BASE::DATA::Vector2I{0, 40};
    }
};
