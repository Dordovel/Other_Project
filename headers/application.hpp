#ifndef SFMLPROJECT_REBUILD_APPLICATION_HPP
#define SFMLPROJECT_REBUILD_APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include "../struct/event_object.hpp"
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
            PROJECT::EVENT::EventObject _eventPool;

        public:
            void init() override;
            void display() override;
            bool is_open() override;
            PROJECT::EVENT::EventObject event_handler() override;

            bool check_events() override;

            void draw(const DRAWABLE* const object) override;
            void window_close() override;
            void clear() override;
            void set_position(int x, int y) override;
            PROJECT::BASE::DATA::Vector2UI get_desktop_size() const override;
            PROJECT::BASE::DATA::Vector2I get_position() const override;
            PROJECT::BASE::DATA::Vector2UI get_size() const override;

            PROJECT::BASE::DATA::Vector2F map_pixel_to_coords(PROJECT::BASE::DATA::Vector2I position) override;

            PROJECT::BASE::DATA::Vector2F map_pixel_to_coords(int X, int Y) override;

            void set_view(std::shared_ptr<PROJECT::APPLICATION::IView> view) override;

            ~Application() = default;
            Application(const std::string& windowName, int width, int height);
    };
};
#endif //SFMLPROJECT_REBUILD_APPLICATION_HPP
