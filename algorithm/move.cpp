#include "./move.hpp"
#include "../struct/side.hpp"

namespace PROJECT::MOVE
{
	void Move::object_move(MOVABLE* const object , float posX , float posY) noexcept
	{
		object->move ( posX , posY );
	}

	void Move::moveUp(MOVABLE *const object, float clock, float speed) noexcept
	{
		float posX = 0;
		float posY = -(speed * clock);

		object_move(object , posX , posY );
	}

	void Move::moveDown(MOVABLE* const object, float clock, float speed) noexcept
	{
		float posX = 0;
		float posY = speed * clock;

		object_move(object , posX , posY );
	}

	void Move::moveLeft(MOVABLE *const  object, float clock, float speed) noexcept
	{
		float posX = -(speed * clock);
		float posY = 0;

		object_move(object , posX , posY );
	}

	void Move::moveRight(MOVABLE* const object, float clock, float speed) noexcept
	{
		float posX = speed * clock;
		float posY = 0;

		object_move(object, posX, posY);
	}


	void Move::move(Side side, MOVABLE* const object, float clock, float speed) noexcept
	{
		if(side == Side::UP && !this->_up)
		{
			Move::moveUp(object, clock, speed);
		}

		if(side == Side::DOWN && !this->_down)
		{
			Move::moveDown(object, clock, speed);
		}

		if(side == Side::LEFT && !this->_left)
		{
			Move::moveLeft(object, clock, speed);
		}

		if(side == Side::RIGHT && !this->_right)
		{
			Move::moveRight(object, clock, speed);
		}
	}

	void Move::block_side(Side side, bool status) noexcept
	{
		if(side == Side::UP)
		{
			this->_up = status;
		}

		if(side == Side::DOWN)
		{
			this->_down = status;
		}

		if(side == Side::LEFT)
		{
			this->_left = status;
		}

		if(side == Side::RIGHT)
		{
			this->_right = status;
		}
	}

	void Move::block_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = true;
	}

	void Move::unblock_all_side() noexcept
	{
		this->_up = this->_down = this->_left = this->_right = false;
	}
};
