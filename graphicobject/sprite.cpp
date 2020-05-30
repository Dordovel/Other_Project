#include "./sprite.hpp"
#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/side.hpp"

DrawableObject Sprite::draw() const noexcept
{
    return DrawableObject{this->_sprite};
}

void Sprite::move(const Vector2F& step) noexcept
{
	this->move(step.x, step.y);
}

void Sprite::move(float X, float Y) noexcept
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

Vector2F Sprite::get_position() const noexcept
{
    return {this->_sprite->getPosition()};
}

void Sprite::rotate(float angle) noexcept
{
	this->_sprite->rotate(angle);
}

RectangleF Sprite::get_global_bounds() const noexcept
{
    return {this->_sprite->getGlobalBounds()};
}

bool Sprite::collision(const std::shared_ptr<INTERACTION>& object) noexcept
{
    return this->_sprite->getGlobalBounds().contains(object->get_position());
}

bool Sprite::collision(const Vector2F& object) noexcept
{
    return this->_sprite->getGlobalBounds().contains(object);
}

void Sprite::set_id(const std::string& id) noexcept
{
    this->_id = id;
}

std::string Sprite::get_id() const noexcept
{
    return this->_id;
}

Sprite::Sprite(const DataBaseResult& data):_isVisible(true),
											_up(false),
											_down(false),
											_left(false),
											_right(false)
{
    this->_texture = std::make_shared<sf::Texture>();
    this->_texture->loadFromFile(data.rv);
    this->_sprite = std::make_shared<sf::Sprite>(*(_texture), data.rect);
}

void Sprite::set_position(const Vector2F& position) noexcept
{
    this->set_position(position.x, position.y);
}

void Sprite::set_texture_rect(const RectangleI& rect)
{
	this->_sprite->setTextureRect(rect);
}

void Sprite::set_texture(const DataBaseResult& data)
{
    this->_texture = std::make_shared<sf::Texture>();
    this->_texture->loadFromFile(data.rv);
}

void Sprite::set_position(float X, float Y) noexcept
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

void Sprite::visible(bool flag) noexcept
{
    this->_isVisible = flag;
}

bool Sprite::is_visible() noexcept
{
    return this->_isVisible;
}

void Sprite::set_scale(Vector2F scale) noexcept
{
	this->_sprite->setScale(scale);
}

Vector2F Sprite::get_scale() noexcept
{
	return this->_sprite->getScale();
}

void Sprite::block_side(SIDE side, bool status) noexcept
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
