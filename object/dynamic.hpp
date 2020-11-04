#ifndef SFMLPROJECT_REBUILD_OBJECT_DYNAMIC_HPP
#define SFMLPROJECT_REBUILD_OBJECT_DYNAMIC_HPP

namespace PROJECT::BASE::DATA
{
    class Vector2F;
};

class DYNAMIC
{
    public:
        virtual void set_position(PROJECT::BASE::DATA::Vector2F position) noexcept = 0;
        virtual void set_position(float X, float Y) noexcept = 0;
        virtual ~DYNAMIC() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_DYNAMIC_HPP
