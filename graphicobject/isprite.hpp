#pragma once

#include "../object/scalable.hpp"
#include "../object/object.hpp"
#include "../object/textured.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	class ISprite: public OBJECT, public SCALABLE, public TEXTURED
	{
		public:
			virtual ~ISprite() = default;
	};
};
