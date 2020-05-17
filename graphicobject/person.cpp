#include "./person.hpp"
#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/side.hpp"

DrawableObject Person::draw() const
{
    return DrawableObject{this->_sprite};
}

void Person::move(const Vector2F& step)
{
	this->move(step.x, step.y);
}

void Person::move(float X, float Y)
{
	if(this->_up)
		if(Y < 0) Y = 0;

	if(this->_down)
		if(Y > 0) Y = 0;

	if(this->_left)
		if(X < 0) X = 0;

	if(this->_right)
		if(X > 0) X = 0;

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

Person::Person(const DataBaseResult& data):_isVisible(true),
											_up(false),
											_down(false),
											_left(false),
											_right(false)
{
    this->_texture = std::make_shared<sf::Texture>();
    this->_texture->loadFromFile(data.rv);
    this->_sprite = std::make_shared<sf::Sprite>(*(_texture), data.lv);
}

void Person::set_position(const Vector2F& position)
{
    this->set_position(position.x, position.y);
}

void Person::set_position(float X, float Y)
{
	Vector2F current_position = this->get_position();

	if(this->_up)
		if(Y < current_position.y) Y = current_position.y;

	if(this->_down)
		if(Y > current_position.y) Y = current_position.y;

	if(this->_left)
		if(X < current_position.y) X = current_position.x;

	if(this->_right)
		if(X > current_position.y) X = current_position.x;
    
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

void Person::block_side(SIDE side, bool status)
{
	if(side == SIDE::UP)
	{
		this->_up = status;
	}

	if(side == SIDE::DOWN)
	{
		this->_down = status;
	}

	if(side == SIDE::LEFT)
	{
		this->_left = status;
	}

	if(side == SIDE::RIGHT)
	{
		this->_right = status;
	}
}
