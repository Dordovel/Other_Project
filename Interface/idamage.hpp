#pragma once 

namespace PROJECT::NPC
{
	class IDamage
	{
		public:
			virtual float get_damage() const noexcept = 0;
			virtual void set_damage(float damage) noexcept = 0;

			virtual ~IDamage() = default;
	};
};
