#pragma once 

class Vector2F;

class MEASURABLE
{
	public:
		virtual Vector2F get_size() = 0;

		virtual ~MEASURABLE() = default;
};
