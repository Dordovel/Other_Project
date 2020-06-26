#pragma once

namespace PROJECT::NPC
{
	class IHealth
	{
		public:
			virtual int get_health() const noexcept = 0;
			virtual void set_health(int health) noexcept = 0;
	};
};
