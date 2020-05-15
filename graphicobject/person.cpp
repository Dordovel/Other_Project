#include "./person.hpp"
#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"

DrawableObject Person::draw() const
{
    return DrawableObject{this->_sprite};
}

void Person::move(const Vector2F& step)
{
	this->_sprite->move(step);
}

void Person::move(float X, float Y)
{
	this->_sprite->move(X, Y);
}

Vector2F Person::get_position() const
{
    return {this->_sprite->getPosition()};
}

void Person::rotate(float angle)
{
	this->_sprite->rotate(angle);
}

RectangleF Person::get_global_bounds() const
{
    return {this->_sprite->getGlobalBounds()};
}

bool Person::collision(const std::shared_ptr<INTERACTION>& object)
{
    return this->_sprite->getGlobalBounds().contains(object->get_position());
}

void Person::set_id(const std::string& id)
{
    this->_id = id;
}

std::string Person::get_id() const
{
    return this->_id;
}

Person::Person(const DataBaseResult& data):_isVisible(true)
{
    this->_texture = std::make_shared<sf::Texture>();
    this->_texture->loadFromFile(data.rv);
    this->_sprite = std::make_shared<sf::Sprite>(*(_texture), data.lv);
}

void Person::set_position(const Vector2F& position)
{
//    this->_sprite->setPosition(position);
    this->set_position(position.x, position.y);
}

void Person::set_position(float X, float Y)
{
	this->_sprite->setPosition(X, Y);
}

void Person::visible(bool flag)
{
    this->_isVisible = flag;
}

bool Person::is_visible()
{
    return this->_isVisible;
}

void Person::set_scale(Vector2F scale)
{
	this->_sprite->setScale(scale);
}

Vector2F Person::get_scale()
{
	return this->_sprite->getScale();
}

int Person::get_health() const
{
	return this->_health;
}

void Person::set_health(int health)
{
	this->_health = health;
}
