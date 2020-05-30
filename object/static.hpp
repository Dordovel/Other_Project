#pragma once


class RectangleF;
class Vector2F;

class STATIC
{
    public:
		virtual RectangleF get_global_bounds() const noexcept = 0;

        virtual Vector2F get_position() const noexcept = 0;

        virtual ~STATIC() = default;
};
