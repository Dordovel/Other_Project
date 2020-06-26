#pragma once

#include "../object/scalable.hpp"
#include "../object/object.hpp"
#include "../object/animated.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	class ISprite: public OBJECT, public SCALABLE, public ANIMATED
	{
		public:
			virtual ~ISprite() = default;
	};
};
