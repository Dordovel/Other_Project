#include "../headers/events.hpp"

void Events::set_close_window_event(const std::function<void()>& closeWindowEvent)
{
    this->_closeWindowEvent = closeWindowEvent;
}

EventObject& Events::get_event_object()
{
    return this->_eventObject;
}

void Events::add_user_event(const std::function<void()>& event)
{
    this->_gameEvents.emplace_back(event);
}

void Events::add_key_event(int key , const std::function<void()>& fun , EventHandlerType eventType)
{
    Events::EventHandler eventHandler;
    eventHandler.key = static_cast<Keyboard_Key::Key>(key);
    eventHandler.fun = fun;

    if (eventType == EventHandlerType::EVENT_LOOP)
    {
        this->_eventLoopPool.push_back(eventHandler);
    }
    else if(eventType == EventHandlerType::NONE)
    {
        this->_eventNonePool.push_back(eventHandler);
    }
}

void Events::catch_events_loop()
{
    if(this->_eventObject.type == EventObject::Closed)
    {
        this->_closeWindowEvent();
    }

    for(const Events::EventHandler& eventHandlerLoop : this->_eventLoopPool)
    {
        if((this->_eventObject.type == EventObject::KeyPressed) && (this->_eventObject.key.code == eventHandlerLoop.key))
        {
            eventHandlerLoop.fun();
        }
    }

    this->catch_mouse_pressed_event();
    this->catch_mouse_mouse_moved_event();
    this->catch_mouse_enter_event();
    this->catch_mouse_wheel_scrolled_event();
    this->catch_mouse_released_event();
}

void Events::catch_events_none()
{
    for (const Events::EventHandler& eventHandlerNone : this->_eventNonePool)
    {
        if(Keyboard_Key::isKeyPressed(eventHandlerNone.key))
        {
            eventHandlerNone.fun();
        }
    }

    for(const std::function<void()>& fun : this->_gameEvents)
    {
        fun();
    }
}

void Events::catch_mouse_wheel_scrolled_event()
{
    if (this->_eventObject.type == sf::Event::MouseWheelScrolled)
    {
		for(const auto& value : this->_eventMouseWheelScrolledPool)
		{
			value.fun(this->_eventObject.mouseWheelScroll.x, this->_eventObject.mouseWheelScroll.y, this->_eventObject.mouseWheelScroll.delta);
		}
    }
}

void Events::catch_mouse_mouse_moved_event()
{
    if (this->_eventObject.type == sf::Event::MouseMoved)
    {
        for(const auto& value : this->_eventMouseMovedPool)
        {
            value.fun(this->_eventObject.mouseMove.x, this->_eventObject.mouseMove.y);
        }
    }
}

void Events::catch_mouse_enter_event()
{
    if (this->_eventObject.type == sf::Event::MouseEntered)
    {
        for(const auto& value : this->_eventMouseEnteredPool)
        {
            value.fun();
        }
    }
}

void Events::catch_mouse_pressed_event()
{
    if (this->_eventObject.type == sf::Event::MouseButtonPressed)
    {
        auto value = this->_eventMousePressedPool.find(this->_eventObject.mouseButton.button);

        if (value != this->_eventMousePressedPool.end())
        {
            value->second.fun((this->_eventObject.mouseButton.x - 10), (this->_eventObject.mouseButton.y - 10));
        }
    }
}

void Events::catch_mouse_released_event()
{
    if (this->_eventObject.type == sf::Event::MouseButtonReleased)
    {
        for(const auto& value : this->_eventMouseReleasedPool)
        {
            value.fun();
        }
    }
}

void Events::mouse_button_pressed(int key, const std::function<void(int X, int Y)>& fun)
{
    Events::EventHandlerMousePressed eventHandler;
    eventHandler.fun = fun;
    auto value = static_cast<Mouse_Key::Button>(key);

    this->_eventMousePressedPool.emplace(value ,eventHandler);
}

void Events::mouse_moved(const std::function<void(int X, int Y)>& fun)
{
    Events::EventHandlerMouseMoved eventHandler;
    eventHandler.fun = fun;

    this->_eventMouseMovedPool.push_back(eventHandler);
}

void Events::mouse_wheel_scrolled(const std::function<void(int X, int Y, int Delta)>& fun)
{
    Events::EventHandlerMouseWheelScrolled eventHandler;
    eventHandler.fun = fun;

    this->_eventMouseWheelScrolledPool.push_back(eventHandler);
}

void Events::mouse_entered(const std::function<void()>& fun)
{
    Events::EventHandlerMouseEntered eventHandler;
    eventHandler.fun = fun;

    this->_eventMouseEnteredPool.push_back(eventHandler);
}

void Events::mouse_button_released(const std::function<void()>& fun)
{
    Events::EventHandlerMouseReleased eventHandler;
    eventHandler.fun = fun;

    this->_eventMouseReleasedPool.push_back(eventHandler);
}

std::string Events::get_id() const
{
	return this->_id;
}

void Events::set_id(const std::string& id)
{
	this->_id = id;
}
