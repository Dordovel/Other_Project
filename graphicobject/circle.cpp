#include "struct/drawable_object.hpp"
#include "struct/vector_object.hpp"
#include "./circle.hpp"
#include "struct/rect_object.hpp"
#include "../struct/side.hpp"
#include "../struct/rgb.hpp"

namespace PROJECT::BASE::GRAPHIC
{
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

		std::cout<<"Circle(): "<<this->get_id()<< '\n';
	}

	Circle::~Circle()
	{
		std::cout<<"\t~Circle(): "<< this->get_id()<< '\n';
	}

	std::shared_ptr<OBJECT> Circle::clone() noexcept
	{
		std::shared_ptr<Circle> copy = std::make_shared<Circle>(*this);
		copy->_circleShape = std::make_shared<sf::CircleShape>(*(this->_circleShape.get()));

		return copy;
	}

	PROJECT::BASE::DATA::DrawableObject Circle::draw() const noexcept
	{
		return {this->_circleShape};
	}

	std::string Circle::get_id() const noexcept
	{
		return this->_id;
	}

	void Circle::set_id(std::string_view id) noexcept
	{
		this->_id = id;
	}

	void Circle::set_position(const PROJECT::BASE::DATA::Vector2F& position) noexcept
	{
		this->set_position(position.x, position.y);
	}

	void Circle::set_position(float X, float Y) noexcept
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

		this->_circleShape->setPosition(X, Y);
	}

	bool Circle::collision(const std::shared_ptr<INTERACTION>& object) noexcept
	{
		return this->_circleShape->getGlobalBounds().contains(object->get_position());
	}

	bool Circle::collision(const PROJECT::BASE::DATA::Vector2F& vec) noexcept
	{
		return this->_circleShape->getGlobalBounds().contains(vec);
	}

	bool Circle::collision(const PROJECT::BASE::DATA::RectangleF& rect) noexcept
	{
		return this->_circleShape->getGlobalBounds().intersects(rect);
	}

	void Circle::move(const PROJECT::BASE::DATA::Vector2F& step) noexcept
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

	PROJECT::BASE::DATA::Vector2F Circle::get_position() const  noexcept
	{
		return this->_circleShape->getPosition();
	}

	PROJECT::BASE::DATA::RectangleF Circle::get_global_bounds() const noexcept
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

	void Circle::set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept
	{
		this->_circleShape->setScale(scale);
	}

	PROJECT::BASE::DATA::Vector2F Circle::get_scale() noexcept
	{
		return this->_circleShape->getScale();
	}

	void Circle::block_side(PROJECT::MOVE::Side side, bool status) noexcept
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

	void Circle::block_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = true;
	}

	void Circle::unblock_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = false;
	}

	void Circle::set_color(const Color& color)
	{
		this->_circleShape->setFillColor(RGB::color(color));
	}

	void Circle::set_points_count(int points)
	{
		this->_circleShape->setPointCount(points);
	}
};
