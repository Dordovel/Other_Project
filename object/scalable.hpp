#pragma once

class Vector2F;

class SCALABLE
{
	public:
		virtual void set_scale(Vector2F scale) = 0;
		virtual Vector2F get_scale() = 0;
		
		virtual ~SCALABLE() = default;
};
