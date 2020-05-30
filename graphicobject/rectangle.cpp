#include "./rectangle.hpp"

#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/side.hpp"

Rectangle::Rectangle(float width, float height):Rectangle(Vector2F(width, height)){}

Rectangle::Rectangle(Vector2F size):_rectangle(new sf::RectangleShape(size)),
															_isVisible(false),
															_up(false),
															_down(false),
															_left(false),
															_right(false)
{
    this->_rectangle->setFillColor(sf::Color::Green);
    this->_rectangle->setOutlineColor(sf::Color::Black);
}

DrawableObject Rectangle::draw() const noexcept
{
    return {this->_rectangle};
}

void Rectangle::set_id(const std::string& id) noexcept
{
    this->_id = id;
}

std::string Rectangle::get_id() const noexcept
{
    return this->_id;
}

void Rectangle::set_position(const Vector2F& position) noexcept
{
    this->set_position(position.x, position.y);
}

void Rectangle::set_position(float X, float Y) noexcept
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

    this->_rectangle->setPosition(X, Y);
}

void Rectangle::rotate(float angle) noexcept
{
    this->_rectangle->rotate(angle);
}

bool Rectangle::collision(const std::shared_ptr<INTERACTION>& object) noexcept
{
    return this->_rectangle->getGlobalBounds().contains(object->get_position());
}

bool Rectangle::collision(const Vector2F& object) noexcept
{
    return this->_rectangle->getGlobalBounds().contains(object);
}

void Rectangle::move(const Vector2F& step) noexcept
{
    this->move(step.x, step.y);
}

void Rectangle::move(float X, float Y) noexcept
{
	if(this->_up)
		if(Y < 0) Y = 0;

	if(this->_down)
		if(Y > 0) Y = 0;

	if(this->_left)
		if(X < 0) X = 0;

	if(this->_right)
		if(X > 0) X = 0;

    this->_rectangle->move(X, Y);
}

Vector2F Rectangle::get_position() const  noexcept
{
    return this->_rectangle->getPosition();
}

RectangleF Rectangle::get_global_bounds() const noexcept
{
    return this->_rectangle->getGlobalBounds();
}

void Rectangle::visible(bool flag) noexcept
{
    this->_isVisible = flag;
}

bool Rectangle::is_visible() noexcept
{
    return this->_isVisible;
}

void Rectangle::set_scale(Vector2F scale) noexcept
{
	this->_rectangle->setScale(scale);
}

Vector2F Rectangle::get_scale() noexcept
{
	return this->_rectangle->getScale();
}

void Rectangle::block_side(SIDE side, bool status) noexcept
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

void Rectangle::set_color(const Color& color)
{
	this->_rectangle->setFillColor(color);
}
