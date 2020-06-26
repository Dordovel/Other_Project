#pragma once

namespace PROJECT::NPC
{
	class IPoints
	{
		public:
			virtual int get_points() const noexcept = 0;
			virtual void set_points(int points) noexcept = 0;
	};
};
