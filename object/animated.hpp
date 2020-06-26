#pragma once

namespace PROJECT::BASE::DATA
{
	class RectangleI;
};

class ANIMATED
{
	public:
		virtual void set_texture_rect(const PROJECT::BASE::DATA::RectangleI& rect) = 0;

		virtual ~ANIMATED() = default;
};
