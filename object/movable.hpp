#pragma once

namespace PROJECT::BASE::DATA
{
    class Vector2F;
};

class MOVABLE
{
    public:
        virtual void move(const PROJECT::BASE::DATA::Vector2F& step) noexcept = 0;
        virtual void move(float X, float Y) noexcept = 0;
        virtual ~MOVABLE() = default;
};
