#pragma once

class DataBaseResult;
class RectangleI;

class ANIMATED
{
	public:
		virtual void set_texture(const DataBaseResult& data) = 0;
		virtual void set_texture_rect(const RectangleI& rect) = 0;

		virtual ~ANIMATED() = default;
};
