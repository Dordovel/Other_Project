#pragma once

#include "./imove.hpp"
#include "../struct/vector_object.hpp"

namespace PROJECT::MOVE
{
	class Move : public IMove
	{
		private:
			static void object_move(const std::shared_ptr<MOVABLE>& object , float posX , float posY) noexcept;

			static void moveUp(const std::shared_ptr<MOVABLE>& object, float clock, float speed) noexcept;

			static void moveDown(const std::shared_ptr<MOVABLE>& object, float clock, float speed) noexcept;

			static void moveLeft(const std::shared_ptr<MOVABLE>& object, float clock, float speed) noexcept;

			static void moveRight(const std::shared_ptr<MOVABLE>& object, float clock, float speed) noexcept;

			bool _up;
			bool _down;
			bool _left;
			bool _right;

		public:
			void move(PROJECT::MOVE::Side side, const std::shared_ptr<MOVABLE>& object, float clock, float speed) noexcept override;

			void block_side(PROJECT::MOVE::Side side, bool status) noexcept override;

			void block_all_side() noexcept override;

			void unblock_all_side() noexcept override;

			~Move() = default;
	};
};
