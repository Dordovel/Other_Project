#include "./text.hpp"
#include "../struct/drawable_object.hpp"
#include "../struct/vector_object.hpp"
#include "./circle.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/side.hpp"
#include "../struct/rgb.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	Text::Text(std::string_view pathToFontFile):_text(std::make_shared<sf::Text>()),
																	_isVisible(true),
																	_up(false),
																	_down(false),
																	_left(false),
																	_right(false)
	{
		this->_font.loadFromFile(pathToFontFile.data());
		this->_text->setFont(this->_font);
		std::cout<<"Text(): "<< this->get_id()<< '\n';
	}

	Text::~Text()
	{
		std::cout<<"\t~Text(): "<< this->get_id()<< '\n';
	}

	std::unique_ptr<OBJECT> Text::clone() noexcept
	{
		std::unique_ptr<Text> copy = std::make_unique<Text>(*this);
		copy->_text = std::make_shared<sf::Text>(*(this->_text.get()));

		return copy;
	}

	PROJECT::BASE::DATA::DrawableObject Text::draw() const noexcept
	{
		return {this->_text};
	}

	std::string Text::get_id() const noexcept
	{
		return this->_id;
	}

	void Text::set_id(std::string_view id) noexcept
	{
		this->_id = id;
	}

	void Text::set_position(PROJECT::BASE::DATA::Vector2F position) noexcept
	{
		this->set_position(position.x, position.y);
	}

	void Text::set_position(float X, float Y) noexcept
	{
		PROJECT::BASE::DATA::Vector2F current_position = this->get_position();

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

	bool Text::collision(const INTERACTION* const object) const noexcept
	{
		return this->_text->getGlobalBounds().intersects(object->get_global_bounds());
	}

	bool Text::collision(PROJECT::BASE::DATA::Vector2F vec) const noexcept
	{
		return this->_text->getGlobalBounds().contains(vec);
	}

	bool Text::collision(PROJECT::BASE::DATA::RectangleF rect) const noexcept
	{
		return this->_text->getGlobalBounds().intersects(rect);
	}

	void Text::move(PROJECT::BASE::DATA::Vector2F step) noexcept
	{
		this->move(step.x, step.y);
	}

	void Text::move(float X, float Y) noexcept
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

	PROJECT::BASE::DATA::Vector2F Text::get_position() const noexcept
	{
		return this->_text->getPosition();
	}

	PROJECT::BASE::DATA::RectangleF Text::get_global_bounds() const noexcept
	{
		return this->_text->getGlobalBounds();
	}

	void Text::visible(bool flag) noexcept
	{
		this->_isVisible = flag;
	}

	bool Text::is_visible() noexcept
	{
		return this->_isVisible;
	}

	void Text::set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept
	{
		this->_text->setScale(scale);
	}

	PROJECT::BASE::DATA::Vector2F Text::get_scale() noexcept
	{
		return this->_text->getScale();
	}

	void Text::set_text(std::string_view str)
	{
		this->_text->setString(str.data());
	}

	void Text::set_font_size(int size)
	{
		this->_text->setCharacterSize(size);
	}

	void Text::set_color(GRAPHIC::Color color)
	{
		this->_text->setFillColor(RGB::color(color));
	}

	void Text::block_side(PROJECT::MOVE::Side side, bool status) noexcept
	{
		if(side == PROJECT::MOVE::Side::UP)
		{
			this->_up = status;
		}

		if(side == PROJECT::MOVE::Side::DOWN)
		{
			this->_down = status;
		}

		if(side == PROJECT::MOVE::Side::LEFT)
		{
			this->_left = status;
		}

		if(side == PROJECT::MOVE::Side::RIGHT)
		{
			this->_right = status;
		}
	}

	void Text::block_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = true;
	}

	void Text::unblock_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = false;
	}
};
