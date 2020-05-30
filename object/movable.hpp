#pragma once

class Vector2F;

class MOVABLE
{
    public:
        virtual void move(const Vector2F& step) noexcept = 0;
        virtual void move(float X, float Y) noexcept = 0;
        virtual ~MOVABLE() = default;
};
