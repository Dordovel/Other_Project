#include "./text.hpp"
#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "./circle.hpp"
#include "../struct/rectobject.hpp"

Text::Text(const std::string& pathToFontFile):_text(std::make_shared<sf::Text>()),
                            _isVisible(true)
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
    this->_text->setPosition(position);
}

void Text::set_position(float X, float Y)
{
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

void Text::move(const Vector2F& step)
{
    this->_text->move(step);
}

void Text::move(float X, float Y)
{
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

