#pragma once

enum class SIDE;

class MODIFIABLE
{
	public:
		virtual void block_side(SIDE side, bool status) noexcept = 0;

		virtual ~MODIFIABLE() = default;
};
