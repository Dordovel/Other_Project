#pragma once

#include "../object/scalable.hpp"
#include "../object/object.hpp"
#include "../struct/color.hpp"

namespace PROJECT::BASE::GRAPHIC
{
	class IRectangle : public OBJECT, public SCALABLE
	{
		public:
            virtual void set_color(Color color) = 0;
            virtual void set_size(BASE::DATA::Vector2F size) noexcept = 0;
            virtual void set_size(float width, float height) noexcept = 0;
            virtual BASE::DATA::Vector2F get_size() const noexcept = 0;
			virtual ~IRectangle() = default;
	};
};
