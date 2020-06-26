#pragma once

#include <memory>
#include "../Interface/iphysics.hpp"
#include "../Interface/icollection.hpp"
#include "../object/object.hpp"

namespace PROJECT::MOVE
{
	enum class Side;

	class IMove
	{
		public:
			virtual void move(PROJECT::MOVE::Side side, const std::shared_ptr<MOVABLE>& object, float clock, float speed) noexcept = 0;

			virtual void block_side(PROJECT::MOVE::Side side, bool status) noexcept = 0;
			
			virtual ~IMove() = default;
	};
};
