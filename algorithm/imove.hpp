#pragma once

#include <memory>
#include "../Interface/iclock.hpp"
#include "../Interface/iphysics.hpp"
#include "../Interface/icollection.hpp"
#include "../Interface/iobject.hpp"

enum class MoveSide
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class IMove
{
    public:
        virtual void move(std::shared_ptr<IOBJECT> object,
                    std::shared_ptr<IClock> clock,
                    std::shared_ptr<IPhysics> physics,
                    std::shared_ptr<ICollection> checker,
                    Vector2F end, float speed) = 0;

		virtual void move(MoveSide side, const std::shared_ptr<MOVABLE>& object, float clock, float speed) = 0;

		virtual void block_side(MoveSide side, bool status) = 0;

        virtual ~IMove() = default;
};
