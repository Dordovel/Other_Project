#ifndef SFMLPROJECT_REBUILD_OBJECT_MOVABLE_HPP
#define SFMLPROJECT_REBUILD_OBJECT_MOVABLE_HPP

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
#endif //SFMLPROJECT_REBUILD_OBJECT_MOVABLE_HPP
