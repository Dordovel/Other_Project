#include "./text.hpp"
#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "./circle.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/side.hpp"

Text::Text(const std::string& pathToFontFile):_text(std::make_shared<sf::Text>()),
                            _isVisible(true),
							_up(false),
							_down(false),
							_left(false),
							_right(false)
{
	this->_font.loadFromFile(pathToFontFile);
	this->_text->setFont(this->_font);
}

DrawableObject Text::draw() const
{
    return {this->_text};
}

void Text::set_id(const std::string& id)
{
    this->_id = id;
}

std::string Text::get_id() const
{
    return this->_id;
}

void Text::set_position(const Vector2F& position)
{
    this->set_position(position.x, position.y);
}

void Text::set_position(float X, float Y)
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

    this->_text->setPosition(X, Y);
}

void Text::rotate(float angle)
{
    this->_text->rotate(angle);
}

bool Text::collision(const std::shared_ptr<INTERACTION>& object)
{
    return this->_text->getGlobalBounds().contains(object->get_position());
}

bool Text::collision(const Vector2F& object)
{
    return this->_text->getGlobalBounds().contains(object);
}

void Text::move(const Vector2F& step)
{
    this->move(step.x, step.y);
}

void Text::move(float X, float Y)
{
	if(this->_up)
		if(Y < 0) Y = 0;

	if(this->_down)
		if(Y > 0) Y = 0;

	if(this->_left)
		if(X < 0) X = 0;

	if(this->_right)
		if(X > 0) X = 0;

    this->_text->move(X, Y);
}

Vector2F Text::get_position() const
{
    return this->_text->getPosition();
}

RectangleF Text::get_global_bounds() const
{
    return this->_text->getGlobalBounds();
}

void Text::visible(bool flag)
{
    this->_isVisible = flag;
}

bool Text::is_visible()
{
    return this->_isVisible;
}

void Text::set_scale(Vector2F scale)
{
	this->_text->setScale(scale);
}

Vector2F Text::get_scale()
{
	return this->_text->getScale();
}

void Text::set_text(const std::string& str)
{
	this->_text->setString(str);
}

void Text::set_font_size(int size)
{
	this->_text->setCharacterSize(size);
}

void Text::set_color(const Color& color)
{
	this->_text->setFillColor(color);
}

void Text::block_side(SIDE side, bool status)
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
