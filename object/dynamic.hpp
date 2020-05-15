#pragma once

class Vector2F;

class DYNAMIC
{
    public:
        virtual void set_position(const Vector2F& position) = 0;
        virtual void set_position(float X, float Y) = 0;
        virtual void rotate(float angle) = 0;
        virtual ~DYNAMIC() = default;
};
