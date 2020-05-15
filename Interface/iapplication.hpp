#pragma once
#include <memory>
#include "../object/drawable.hpp"
#include "./iview.hpp"

class EventObject;
class Vector2UI;
class Vector2I;

class IApplication
{
    public:
        virtual void init() = 0;
        virtual void display() = 0;
        virtual void clear() = 0;
        virtual bool is_open() =  0;
        virtual void draw(const std::shared_ptr<DRAWABLE>& object) = 0;
        virtual void window_close() = 0;
        virtual bool event_handler(EventObject& eventObject ) = 0;
        virtual Vector2F map_pixel_to_coords(const Vector2I& position) = 0;
        virtual Vector2F map_pixel_to_coords(int X, int Y) = 0;
        virtual void set_position(int x, int y) = 0;
        virtual Vector2I get_position() const = 0;
        virtual Vector2UI get_desktop_size() const = 0;
        virtual Vector2UI get_size() const = 0;
        virtual void set_view(const std::shared_ptr<IView>& view) = 0;
        virtual ~IApplication() = default;
};
