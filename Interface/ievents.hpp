#pragma once
#include <functional>

namespace PROJECT::EVENT
{
    class EventObject;

    enum class EventHandlerType
    {
        EVENT_LOOP,
        NONE
    };

    class IEvents
    {
        public:
            virtual void set_close_window_event(const std::function<void()>& closeWindowEvent) noexcept = 0;
            virtual void key_pressed_event(int key , const std::function<void()>& fun , PROJECT::EVENT::EventHandlerType eventType) noexcept = 0;
            virtual void key_released_event(int key , const std::function<void()>& fun) noexcept = 0;
            virtual void mouse_button_pressed(int key, const std::function<void(int X, int Y)>& fun) noexcept = 0;
            virtual void mouse_button_released(const std::function<void()>& fun) noexcept = 0;
            virtual void mouse_moved(const std::function<void(int X, int Y)>& fun) noexcept = 0;
            virtual void mouse_wheel_scrolled(const std::function<void(int X, int Y, int Delta)>& fun) noexcept = 0;
            virtual void mouse_entered(const std::function<void()>& fun) noexcept = 0;
            virtual void catch_events_loop() = 0;
            virtual void catch_events_none() = 0;
            virtual PROJECT::EVENT::EventObject& get_event_object() noexcept = 0;

            virtual ~IEvents() = default;
    };
};
