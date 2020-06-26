#pragma once

namespace PROJECT::MOVE
{
	enum class Side;
};

class MODIFIABLE
{
	public:
		virtual void block_side(PROJECT::MOVE::Side side, bool status) noexcept = 0;

		virtual void block_all_side() noexcept = 0;

		virtual void unblock_all_side() noexcept = 0;

		virtual ~MODIFIABLE() = default;
};
