#include "../headers/application.hpp"
#include "../struct/drawable_object.hpp"
#include "../struct/event_object.hpp"
#include "../struct/vector_object.hpp"

namespace PROJECT::APPLICATION
{
    const int ANTIALIASINGLEVEL = 8;

    Application::Application(const std::string& windowName, int width, int height): _windowName(windowName),
                                                                        _width(width),
                                                                        _height(height)

    {}

    bool Application::is_open()
    {
        return sf::RenderWindow::isOpen();
    }

    void Application::clear()
    {
        sf::RenderWindow::clear();
    }

    void Application::window_close()
    {
        sf::RenderWindow::close();
    }

    void Application::init()
    {
        sf::ContextSettings setting;
        setting.antialiasingLevel = ANTIALIASINGLEVEL;
        sf::RenderWindow::create(sf::VideoMode(this->_width , this->_height) , this->_windowName, sf::Style::Default, setting);
    }

    PROJECT::EVENT::EventObject Application::event_handler()
    {
        return this->_eventPool;
    }

    void Application::draw(const DRAWABLE* const object)
    {
        sf::RenderWindow::draw(*(object->draw().object));
    }

    void Application::display()
    {   
        if(this->_view)
        {
            sf::RenderWindow::setView(*(this->_view));

            sf::FloatRect rt;
            rt.left = this->_view->getCenter().x - this->_view->getSize().x / 2.f;
            rt.top  = this->_view->getCenter().y - this->_view->getSize().y / 2.f;
            rt.width  = this->_view->getSize().x;
            rt.height = this->_view->getSize().y;

            sf::VertexArray array1(sf::Lines, 2);
            sf::VertexArray array2(sf::Lines, 2);
            sf::VertexArray array3(sf::Lines, 2);
            sf::VertexArray array4(sf::Lines, 2);

            sf::Vector2f position = this->_view->getCenter();

            array1[0].position = {position.x, position.y};
            array1[1].position = {position.x, rt.top + rt.height};
            array1[1].color = sf::Color::Black;
            array1[0].color = sf::Color::Black;

            array2[0].position = {position.x, position.y};
            array2[1].position = {rt.left + rt.width, position.y};
            array2[1].color = sf::Color::Black;
            array2[0].color = sf::Color::Black;

            array3[0].position = {rt.left, position.y};
            array3[1].position = {position.x, position.y};
            array3[1].color = sf::Color::Black;
            array3[0].color = sf::Color::Black;

            array4[0].position = {position.x, position.y};
            array4[1].position = {position.x, rt.top};
            array4[1].color = sf::Color::Black;
            array4[0].color = sf::Color::Black;

            sf::RenderWindow::draw(array1);
            sf::RenderWindow::draw(array2);
            sf::RenderWindow::draw(array3);
            sf::RenderWindow::draw(array4);
        }

        sf::RenderWindow::display();

        this->clear();
    }

    void Application::set_position(int x, int y)
    {
        sf::RenderWindow::setPosition({x, y});
    }

    PROJECT::BASE::DATA::Vector2I Application::get_position() const
    {
        return PROJECT::BASE::DATA::Vector2I(sf::RenderWindow::getPosition());
    }

    PROJECT::BASE::DATA::Vector2UI Application::get_desktop_size() const
    {
        PROJECT::BASE::DATA::Vector2UI size(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().width);
        return size;
    }

    PROJECT::BASE::DATA::Vector2UI Application::get_size() const
    {
        return sf::RenderWindow::getSize();
    }

    void Application::set_view(std::shared_ptr<PROJECT::APPLICATION::IView> view)
    {
        auto pointer = std::dynamic_pointer_cast<sf::View>(view);

        if (pointer)
        {
            this->_view = pointer;
        }
    }

    PROJECT::BASE::DATA::Vector2F Application::map_pixel_to_coords(PROJECT::BASE::DATA::Vector2I position)
    {
        return sf::RenderWindow::mapPixelToCoords(position);// - this->getPosition());
    }

    PROJECT::BASE::DATA::Vector2F Application::map_pixel_to_coords(int X, int Y)
    {
		return this->map_pixel_to_coords({X, Y});
    }

    bool Application::check_events()
    {
        return sf::RenderWindow::pollEvent(this->_eventPool);
    }
};
