#include "../headers/view.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/side.hpp"

View::View(float X, float Y, float Width, float Height):_up(false),
														_down(false),
														_left(false),
														_right(false)
{
    sf::View::setSize(Width, Height);
    sf::View::setCenter(X, Y);
}

View::View(const Vector2F& position, float Width, float Height):View(position.x,
																	position.y,
																	Width,
																	Height)
{}

View::View(const Vector2F& position, const Vector2F& size):View(position.x,
																	position.y,
																	size.x,
																	size.y)
{}

View::View(const Vector2F& size):View(0, 0, size.x, size.y){}

void View::zoom(float zoom) noexcept
{
    sf::View::zoom(zoom);
}

void View::set_position(const Vector2F& position) noexcept
{
    this->set_position(position.x, position.y);
}

void View::rotate(float angle) noexcept
{
    sf::View::rotate(angle);
}

bool View::collision(const std::shared_ptr<INTERACTION>& object) noexcept
{
    return this->get_global_bounds().contains(object->get_position());
}

bool View::collision(const Vector2F& object) noexcept
{
    return this->get_global_bounds().contains(object);
}

void View::move(const Vector2F& step) noexcept
{
    this->move(step.x, step.y);
}

void View::move(float X, float Y) noexcept
{
	if(this->_up)
		if(Y < 0) Y = 0;

	if(this->_down)
		if(Y > 0) Y = 0;

	if(this->_left)
		if(X < 0) X = 0;

	if(this->_right)
		if(X > 0) X = 0;

    sf::View::move(X, Y);
}

Vector2F View::get_position() const noexcept
{
    return sf::View::getCenter();
}

RectangleF View::get_global_bounds() const noexcept
{
    sf::FloatRect rt;
    rt.left = sf::View::getCenter().x - sf::View::getSize().x / 2.f;
    rt.top  = sf::View::getCenter().y - sf::View::getSize().y / 2.f;
    rt.width  = sf::View::getSize().x;
    rt.height = sf::View::getSize().y;

    return rt;
}

void View::set_position(float X, float Y) noexcept
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
    
	sf::View::setCenter(X, Y);
}

Vector2F View::get_size() const noexcept
{
	return sf::View::getSize();
}

void View::set_size(const Vector2F& size) noexcept
{
	sf::View::setSize(size);
}

void View::set_size(float x, float y) noexcept
{
	sf::View::setSize(x, y);
}

void View::block_side(SIDE side, bool status) noexcept
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
