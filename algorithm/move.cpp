#include "./move.hpp"
#include <thread>
#include <chrono>
#include "../headers/clock.hpp"
#include "../headers/physics.hpp"

using namespace std::chrono_literals;

Move::~Move()
{
    for (auto&& [key, value] : this->_pool)
    {
        if(value->isActive)
        {
            *value->isActive = false;
            pthread_join(value->pthread, nullptr);
            delete value;
        }
        delete value;
    }
}

void* Move::work(void* params)
{
    printf("Thread Start\n");

    auto* param = static_cast<Move::ThreadParams*>(params);

    bool X = true;
    bool Y = true;
    int vector2F_X;
    int vector2F_Y;
    Vector2F position;

    while(*param->isActive && (X || Y))
    {
        position = param->object->get_position();
        vector2F_X = position.x - param->end.x;
        vector2F_Y = position.y - param->end.y;

        if (vector2F_X > 10 || vector2F_X < -10)
        {
            if (vector2F_X < 0)
            {
				Move::moveRight(param->object, param->clock->get_time(), param->speed);
            }
            else if (vector2F_X > 0)
            {
				Move::moveLeft(param->object, param->clock->get_time(), param->speed);
            }
        }
        else{X = false;}

        if (vector2F_Y > 10 || vector2F_Y < -10)
        {
            if (vector2F_Y < 0)
            {
				Move::moveDown(param->object, param->clock->get_time(), param->speed);
            }
            else if (vector2F_Y > 0)
            {
				Move::moveUp(param->object, param->clock->get_time(), param->speed);
            }
        }
        else{Y = false;}

        std::this_thread::sleep_for(5ms);
    }

    printf("Thread End\n");
    *param->isActive = false;

    pthread_exit(nullptr);
}

void Move::move(std::shared_ptr<IOBJECT> object,
        std::shared_ptr<IClock> clock,
        std::shared_ptr<IPhysics> physics,
        std::shared_ptr<ICollection> checker,
        Vector2F end, float speed)
{
    auto result = this->_pool.find(object->get_id());

    if (result != this->_pool.end())
    {
        result->second->object = object;
        result->second->checker = checker;
        result->second->physics = physics;
        result->second->end = end;
        result->second->clock = clock;
        result->second->speed = speed;

        if (!(*result->second->isActive))
        {
            *result->second->isActive = true;

            pthread_attr_t pthreadAttr;
            pthread_attr_init(&pthreadAttr);
            pthread_create(&result->second->pthread, &pthreadAttr, Move::work, result->second);
        }
    }
    else
    {
        this->_pool.emplace(object->get_id(), new ThreadParams);

        this->move(object, clock, physics, checker, end, speed);
    }
}

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

void Move::move(MoveSide side, const std::shared_ptr<MOVABLE>& object, float clock, float speed)
{
	if(side == MoveSide::UP && !this->_up)
	{
		Move::moveUp(object, clock, speed);
	}

	if(side == MoveSide::DOWN && !this->_down)
	{
		Move::moveDown(object, clock, speed);
	}

	if(side == MoveSide::LEFT && !this->_left)
	{
		Move::moveLeft(object, clock, speed);
	}

	if(side == MoveSide::RIGHT && !this->_right)
	{
		Move::moveRight(object, clock, speed);
	}
}

void Move::block_side(MoveSide side, bool status)
{
	if(side == MoveSide::UP)
	{
		this->_up = status;
	}

	if(side == MoveSide::DOWN)
	{
		this->_down = status;
	}

	if(side == MoveSide::LEFT)
	{
		this->_left = status;
	}

	if(side == MoveSide::RIGHT)
	{
		this->_right = status;
	}
}
