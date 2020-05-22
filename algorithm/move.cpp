#include "./move.hpp"
#include <thread>
#include <chrono>
#include "../headers/clock.hpp"
#include "../headers/physics.hpp"
#include "../struct/side.hpp"


void Move::game_object_move(const std::shared_ptr<MOVABLE>& object , float posX , float posY)
{
	object->move ( posX , posY );
}

void Move::moveUp(const std::shared_ptr<MOVABLE>& object, float clock, float speed)
{
	float posX = 0;
	float posY = -(speed * clock);

	game_object_move(object , posX , posY );
}

void Move::moveDown(const std::shared_ptr<MOVABLE>& object, float clock, float speed)
{
	float posX = 0;
	float posY = speed * clock;

	game_object_move(object , posX , posY );
}

void Move::moveLeft(const std::shared_ptr<MOVABLE>& object, float clock, float speed)
{
	float posX = -(speed * clock);
	float posY = 0;

	game_object_move(object , posX , posY );
}

void Move::moveRight(const std::shared_ptr<MOVABLE>& object, float clock, float speed)
{
	float posX = speed * clock;
	float posY = 0;

	game_object_move(object, posX, posY);
}

void Move::move(SIDE side, const std::shared_ptr<MOVABLE>& object, float clock, float speed)
{
	if(side == SIDE::UP && !this->_up)
	{
		Move::moveUp(object, clock, speed);
	}

	if(side == SIDE::DOWN && !this->_down)
	{
		Move::moveDown(object, clock, speed);
	}

	if(side == SIDE::LEFT && !this->_left)
	{
		Move::moveLeft(object, clock, speed);
	}

	if(side == SIDE::RIGHT && !this->_right)
	{
		Move::moveRight(object, clock, speed);
	}
}

void Move::block_side(SIDE side, bool status)
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
