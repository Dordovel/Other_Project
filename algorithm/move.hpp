#pragma once

#include "./imove.hpp"
#include "../struct/vectorobject.hpp"
#include <pthread.h>

class Move : public IMove
{
    private:

        struct ThreadParams
        {
            bool* isActive;
            pthread_t pthread;
            std::shared_ptr<IPhysics> physics;
            std::shared_ptr<ICollection> checker;
            std::shared_ptr<IOBJECT> object;
            Vector2F end;
            std::shared_ptr<IClock> clock;
            float speed;
        };

        static void* work(void* params);

		static void game_object_move(const std::shared_ptr<MOVABLE>& object , float posX , float posY);

		static void moveUp(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		static void moveDown(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		static void moveLeft(const std::shared_ptr<MOVABLE>& object, float clock, float speed);

		static void moveRight(const std::shared_ptr<MOVABLE>& object, float clock, float speed);


        std::map<std::string, Move::ThreadParams*> _pool;

		bool _up;
		bool _down;
		bool _left;
		bool _right;

    public:

        void move(std::shared_ptr<IOBJECT> object,
                std::shared_ptr<IClock> clock,
                std::shared_ptr<IPhysics> physics,
                std::shared_ptr<ICollection> checker,
                Vector2F end, float speed) override;

		 void move(MoveSide side, const std::shared_ptr<MOVABLE>& object, float clock, float speed) override;

		 void block_side(MoveSide side, bool status) override;

		~Move();
};
