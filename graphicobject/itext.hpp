#pragma once

#include "../object/scalable.hpp"
#include "../object/object.hpp"
#include "../struct/color.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	class IText : public OBJECT, public SCALABLE
	{
		public:
            virtual void set_text(std::string_view str) = 0;
            virtual void set_font_size(int size) = 0;
            virtual void set_color(const Color& color) = 0;
			virtual ~IText() = default;
	};
};
