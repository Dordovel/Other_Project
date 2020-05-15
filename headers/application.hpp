#pragma once
#include <SFML/Graphics.hpp>
#include "../Interface/iapplication.hpp"

class Application : public sf::RenderWindow , public IApplication
{
    private:
		std::string _windowName;
        int _width;
        int _height;
        std::shared_ptr<sf::View> _view;

    public:
        void init() override;
        void display() override;
        bool is_open() override;
        bool event_handler(EventObject& eventObject) override;
        void draw(const std::shared_ptr<DRAWABLE>& object) override;
        void window_close() override;
        void clear() override;
        void set_position(int x, int y) override;
        Vector2UI get_desktop_size() const override;
        Vector2I get_position() const override;
        Vector2UI get_size() const override;

        Vector2F map_pixel_to_coords(const Vector2I& position) override;

        Vector2F map_pixel_to_coords(int X, int Y) override;

        void set_view(const std::shared_ptr<IView>& view) override;

        ~Application() = default;
        Application(const std::string& windowName, int width, int height);
};
