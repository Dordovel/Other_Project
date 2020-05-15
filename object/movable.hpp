#pragma once

class Vector2F;

class MOVABLE
{
    public:
        virtual void move(const Vector2F& step) = 0;
        virtual void move(float X, float Y) = 0;
        virtual ~MOVABLE() = default;
};
