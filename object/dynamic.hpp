#pragma once

namespace PROJECT::BASE::DATA
{
    class Vector2F;
};

class DYNAMIC
{
    public:
        virtual void set_position(const PROJECT::BASE::DATA::Vector2F& position) noexcept = 0;
        virtual void set_position(float X, float Y) noexcept = 0;
        virtual ~DYNAMIC() = default;
};
