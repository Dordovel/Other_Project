#include "./sprite.hpp"
#include "struct/drawable_object.hpp"
#include "struct/vector_object.hpp"
#include "../struct/side.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	Sprite::Sprite(const PROJECT::DATABASE::DataBaseResult& data):_isVisible(true),
																	_up(false),
																	_down(false),
																	_left(false),
																	_right(false)
	{
		this->_texture = std::make_shared<sf::Texture>();
		this->_texture->loadFromFile(data.rv);
		this->_sprite = std::make_shared<sf::Sprite>(*(_texture), data.rect);

		std::cout<<"Sprite(): "<<this->get_id()<< '\n';
	}

	Sprite::~Sprite()
	{
		std::cout<<"\t~Sprite(): "<<this->get_id()<< '\n';
	}

	std::shared_ptr<OBJECT> Sprite::clone() noexcept
	{
		std::shared_ptr<Sprite> copy = std::make_shared<Sprite>(*this);
		copy->_sprite = std::make_shared<sf::Sprite>(*(this->_sprite.get()));
		copy->_texture = std::make_shared<sf::Texture>(*(this->_texture.get()));

		return copy;
	}

	PROJECT::BASE::DATA::DrawableObject Sprite::draw() const noexcept
	{
		return {this->_sprite};
	}

	void Sprite::move(const PROJECT::BASE::DATA::Vector2F& step) noexcept
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

	PROJECT::BASE::DATA::Vector2F Sprite::get_position() const noexcept
	{
		return this->_sprite->getPosition();
	}

	PROJECT::BASE::DATA::RectangleF Sprite::get_global_bounds() const noexcept
	{
		return this->_sprite->getGlobalBounds();
	}

	bool Sprite::collision(const std::shared_ptr<INTERACTION>& object) noexcept
	{
		return this->_sprite->getGlobalBounds().intersects(object->get_global_bounds());
	}

	bool Sprite::collision(const PROJECT::BASE::DATA::Vector2F& vec) noexcept
	{
		return this->_sprite->getGlobalBounds().contains(vec);
	}

	bool Sprite::collision(const PROJECT::BASE::DATA::RectangleF& rect) noexcept
	{
		return this->_sprite->getGlobalBounds().intersects(rect);
	}

	std::string Sprite::get_id() const noexcept
	{
		return this->_id;
	}

	void Sprite::set_id(std::string_view id) noexcept
	{
		this->_id = id;
	}

	void Sprite::set_position(const PROJECT::BASE::DATA::Vector2F& position) noexcept
	{
		this->set_position(position.x, position.y);
	}

	void Sprite::set_texture_rect(const PROJECT::BASE::DATA::RectangleI& rect)
	{
		this->_sprite->setTextureRect(rect);
	}

	void Sprite::set_position(float X, float Y) noexcept
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

	void Sprite::set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept
	{
		this->_sprite->setScale(scale);
	}

	PROJECT::BASE::DATA::Vector2F Sprite::get_scale() noexcept
	{
		return this->_sprite->getScale();
	}

	void Sprite::block_side(PROJECT::MOVE::Side side, bool status) noexcept
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

	void Sprite::block_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = true;
	}

	void Sprite::unblock_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = false;
	}
};
