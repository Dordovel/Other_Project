#pragma once
#include <SFML/Graphics.hpp>
#include "../Interface/iapplication.hpp"

namespace PROJECT::APPLICATION
{
    class Application final : public sf::RenderWindow , public PROJECT::APPLICATION::IApplication
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
            bool event_handler(PROJECT::EVENT::EventObject& eventObject) override;
            void draw(const std::shared_ptr<DRAWABLE>& object) override;
            void window_close() override;
            void clear() override;
            void set_position(int x, int y) override;
            PROJECT::BASE::DATA::Vector2UI get_desktop_size() const override;
            PROJECT::BASE::DATA::Vector2I get_position() const override;
            PROJECT::BASE::DATA::Vector2UI get_size() const override;

            PROJECT::BASE::DATA::Vector2F map_pixel_to_coords(const PROJECT::BASE::DATA::Vector2I& position) override;

            PROJECT::BASE::DATA::Vector2F map_pixel_to_coords(int X, int Y) override;

            void set_view(const std::shared_ptr<PROJECT::APPLICATION::IView>& view) override;

            ~Application() = default;
            Application(const std::string& windowName, int width, int height);
    };
};