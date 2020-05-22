#pragma once

#include "./imove.hpp"
#include "../struct/vectorobject.hpp"
#include <pthread.h>

class Move : public IMove
{
    private:
		static void game_object_move(const std::shared_ptr<MOVABLE>& object , float posX , float posY);

		static void moveUp(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		static void moveDown(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		static void moveLeft(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		static void moveRight(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		bool _up;
		bool _down;
		bool _left;
		bool _right;

    public:
		void move(SIDE side, const std::shared_ptr<MOVABLE>& object, float clock, float speed) override;

		void block_side(SIDE side, bool status) override;

		~Move() = default;
};
