#pragma once

class Vector2F;

class DYNAMIC
{
    public:
        virtual void rotate(float angle) noexcept = 0;
        virtual void set_position(const Vector2F& position) noexcept = 0;
        virtual void set_position(float X, float Y) noexcept = 0;
        virtual ~DYNAMIC() = default;
};
