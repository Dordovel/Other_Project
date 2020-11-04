#pragma once

#include "../object/object.hpp"
#include "../object/scalable.hpp"
#include "../struct/color.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	class ICircle : public OBJECT, public SCALABLE
	{
		public:
            virtual void set_color(Color color) = 0;
            virtual void set_points_count(int points) = 0;
			virtual ~ICircle() = default;
	};
};
