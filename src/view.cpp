#include "../headers/view.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/rectobject.hpp"

void View::zoom(float zoom)
{
    sf::View::zoom(zoom);
}

void View::set_position(const Vector2F& position)
{
    this->set_position(position.x, position.y);
}

void View::rotate(float angle)
{
    sf::View::rotate(angle);
}

bool View::collision(const std::shared_ptr<INTERACTION>& object)
{
    return this->get_global_bounds().contains(object->get_position());
}

void View::move(const Vector2F& step)
{
    sf::View::move(step);
}

void View::move(float X, float Y)
{
    sf::View::move(X, Y);
}

Vector2F View::get_position() const
{
    return sf::View::getCenter();
}

RectangleF View::get_global_bounds() const
{
    sf::FloatRect rt;
    rt.left = sf::View::getCenter().x - sf::View::getSize().x / 2.f;
    rt.top  = sf::View::getCenter().y - sf::View::getSize().y / 2.f;
    rt.width  = sf::View::getSize().x;
    rt.height = sf::View::getSize().y;

    return rt;
}

View::View(float X, float Y, float Width, float Height)
{
    sf::View::setSize(Width, Height);
    sf::View::setCenter(X, Y);
}

View::View(const Vector2F& position, float Width, float Height)
{
    sf::View::setSize(Width, Height);
    sf::View::setCenter(position);
}

void View::set_position(float X, float Y)
{
    sf::View::setCenter(X, Y);
}

Vector2F View::get_size() const
{
	return sf::View::getSize();
}

void View::set_size(const Vector2F& size)
{
	sf::View::setSize(size);
}

void View::set_size(float x, float y)
{
	sf::View::setSize(x, y);
}
