#pragma once

class RectangleF;
class Vector2F;

class STATIC
{
    public:
        virtual Vector2F get_position() const = 0;
        virtual RectangleF get_global_bounds() const = 0;
        virtual ~STATIC() = default;
};
