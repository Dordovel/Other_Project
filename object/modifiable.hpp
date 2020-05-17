#pragma once

enum class SIDE;

class MODIFIABLE
{
	public:
		virtual void block_side(SIDE side, bool status) = 0;

		virtual ~MODIFIABLE() = default;
};
