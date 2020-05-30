#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "./circle.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/side.hpp"

Circle::Circle(float radius):_circleShape(new sf::CircleShape(radius)),
														_isVisible(false),
														_up(false),
														_down(false),
														_left(false),
														_right(false)
{
    this->_circleShape->setFillColor(sf::Color::Green);
    this->_circleShape->setOutlineColor(sf::Color::Black);
    this->_circleShape->setOutlineThickness(radius / 10);
}

DrawableObject Circle::draw() const noexcept
{
    return {this->_circleShape};
}

void Circle::set_id(const std::string& id) noexcept
{
    this->_id = id;
}

std::string Circle::get_id() const noexcept
{
    return this->_id;
}

void Circle::set_position(const Vector2F& position) noexcept
{
    this->set_position(position.x, position.y);
}

void Circle::set_position(float X, float Y) noexcept
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

    this->_circleShape->setPosition(X, Y);
}

void Circle::rotate(float angle) noexcept
{
    this->_circleShape->rotate(angle);
}

bool Circle::collision(const std::shared_ptr<INTERACTION>& object) noexcept
{
    return this->_circleShape->getGlobalBounds().contains(object->get_position());
}

bool Circle::collision(const Vector2F& object) noexcept
{
    return this->_circleShape->getGlobalBounds().contains(object);
}

void Circle::move(const Vector2F& step) noexcept
{
    this->move(step.x, step.y);
}

void Circle::move(float X, float Y) noexcept
{
	if(this->_up)
		if(Y < 0) Y = 0;

	if(this->_down)
		if(Y > 0) Y = 0;

	if(this->_left)
		if(X < 0) X = 0;

	if(this->_right)
		if(X > 0) X = 0;

    this->_circleShape->move(X, Y);
}

Vector2F Circle::get_position() const  noexcept
{
    return this->_circleShape->getPosition();
}

RectangleF Circle::get_global_bounds() const noexcept
{
    return this->_circleShape->getGlobalBounds();
}

void Circle::visible(bool flag) noexcept
{
    this->_isVisible = flag;
}

bool Circle::is_visible() noexcept
{
    return this->_isVisible;
}

void Circle::set_scale(Vector2F scale) noexcept
{
	this->_circleShape->setScale(scale);
}

Vector2F Circle::get_scale() noexcept
{
	return this->_circleShape->getScale();
}

void Circle::block_side(SIDE side, bool status) noexcept
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

void Circle::set_color(const Color& color)
{
	this->_circleShape->setFillColor(color);
}

void Circle::set_points_count(int points)
{
	this->_circleShape->setPointCount(points);
}
