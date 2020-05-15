#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "./circle.hpp"
#include "../struct/rectobject.hpp"

Circle::Circle(float radius):_circleShape(new sf::CircleShape(radius)),
                            _isVisible(false)
{
    this->_circleShape->setFillColor(sf::Color::Black);
    this->_circleShape->setOutlineColor(sf::Color::Red);
    this->_circleShape->setOutlineThickness(radius / 10);
}

DrawableObject Circle::draw() const
{
    return {this->_circleShape};
}

void Circle::set_id(const std::string& id)
{
    this->_id = id;
}

std::string Circle::get_id() const
{
    return this->_id;
}

void Circle::set_position(const Vector2F& position)
{
    this->_circleShape->setPosition(position);
}

void Circle::set_position(float X, float Y)
{
    this->_circleShape->setPosition(X, Y);
}

void Circle::rotate(float angle)
{
    this->_circleShape->rotate(angle);
}

bool Circle::collision(const std::shared_ptr<INTERACTION>& object)
{
    return this->_circleShape->getGlobalBounds().contains(object->get_position());
}

void Circle::move(const Vector2F& step)
{
    this->_circleShape->move(step);
}

void Circle::move(float X, float Y)
{
    this->_circleShape->move(X, Y);
}

Vector2F Circle::get_position() const 
{
    return this->_circleShape->getPosition();
}

RectangleF Circle::get_global_bounds() const
{
    return this->_circleShape->getGlobalBounds();
}

void Circle::visible(bool flag)
{
    this->_isVisible = flag;
}

bool Circle::is_visible()
{
    return this->_isVisible;
}

void Circle::set_scale(Vector2F scale)
{
	this->_circleShape->setScale(scale);
}

Vector2F Circle::get_scale()
{
	return this->_circleShape->getScale();
}
