#include "./rectangle.hpp"

#include "../struct/drawableobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/side.hpp"
#include "../struct/rgb.hpp"
#include "../struct/databaseresult.hpp"
#include <cassert>

namespace PROJECT::BASE::GRAPHIC
{
	Rectangle::Rectangle(float width, float height, std::string_view id):Rectangle(PROJECT::BASE::DATA::Vector2F{width, height}, id){}

	Rectangle::Rectangle(PROJECT::BASE::DATA::Vector2F size, std::string_view id):_rectangle(std::make_shared<sf::RectangleShape>(size)),
													_id(id),
													_isVisible(false),
													_up(false),
													_down(false),
													_left(false),
													_right(false)
	{
		std::cout<<"Rectangle(): "<< this->get_id()<< '\n';
	}

	Rectangle::~Rectangle()
	{
		std::cout<<"\t~Rectangle(): "<<this->get_id()<< '\n';
	}

	PROJECT::BASE::DATA::DrawableObject Rectangle::draw() const noexcept
	{
		return {this->_rectangle};
	}

	std::string Rectangle::get_id() const noexcept
	{
		return this->_id;
	}

	void Rectangle::set_position(const PROJECT::BASE::DATA::Vector2F& position) noexcept
	{
		this->set_position(position.x, position.y);
	}

	void Rectangle::set_texture(const PROJECT::DATABASE::DataBaseResult& resources)
	{
		this->_texture = std::make_shared<sf::Texture>();
		assert(this->_texture->loadFromFile(resources.rv) && "NOT LOAD");
		this->_rectangle->setTexture(this->_texture.get());
		this->_rectangle->setTextureRect(resources.rect);
	}

	void Rectangle::set_size(const BASE::DATA::Vector2F& size) noexcept
	{
		this->_rectangle->setSize(size);
	}

	void Rectangle::set_size(float width, float height) noexcept
	{
		this->_rectangle->setSize({width, height});
	}

	BASE::DATA::Vector2F Rectangle::get_size() const noexcept
	{
		return this->_rectangle->getSize();
	}

	void Rectangle::set_position(float X, float Y) noexcept
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

		this->_rectangle->setPosition(X, Y);
	}

	bool Rectangle::collision(const std::shared_ptr<INTERACTION>& object) noexcept
	{
		return this->_rectangle->getGlobalBounds().contains(object->get_position());
	}

	bool Rectangle::collision(const PROJECT::BASE::DATA::Vector2F& vec) noexcept
	{
		return this->_rectangle->getGlobalBounds().contains(vec);
	}

	bool Rectangle::collision(const PROJECT::BASE::DATA::RectangleF& rect) noexcept
	{
		return this->_rectangle->getGlobalBounds().intersects(rect);
	}

	void Rectangle::move(const PROJECT::BASE::DATA::Vector2F& step) noexcept
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

	PROJECT::BASE::DATA::Vector2F Rectangle::get_position() const  noexcept
	{
		return this->_rectangle->getPosition();
	}

	PROJECT::BASE::DATA::RectangleF Rectangle::get_global_bounds() const noexcept
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

	void Rectangle::set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept
	{
		this->_rectangle->setScale(scale);
	}

	PROJECT::BASE::DATA::Vector2F Rectangle::get_scale() noexcept
	{
		return this->_rectangle->getScale();
	}

	void Rectangle::block_side(PROJECT::MOVE::Side side, bool status) noexcept
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

	void Rectangle::block_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = true;
	}

	void Rectangle::unblock_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = false;
	}

	void Rectangle::set_color(const Color& color)
	{
		this->_rectangle->setFillColor(RGB::color(color));
	}
};
