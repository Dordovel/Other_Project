#pragma once

namespace PROJECT::NPC
{
	class IArmor
	{
		public:

			virtual float get_armor() const noexcept = 0;
			virtual void set_armor(float damage) noexcept = 0;
	};
};
