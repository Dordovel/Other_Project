#ifndef SFMLPROJECT_REBUILD_OBJECT_INTERACTION_HPP
#define SFMLPROJECT_REBUILD_OBJECT_INTERACTION_HPP

#include "./static.hpp"
#include <memory>

class INTERACTION : public STATIC
{
    public:
        virtual bool collision(const INTERACTION* const object) const noexcept = 0;
        virtual bool collision(PROJECT::BASE::DATA::Vector2F vec) const noexcept = 0;
        virtual bool collision(PROJECT::BASE::DATA::RectangleF rect) const noexcept = 0;
        virtual ~INTERACTION() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_INTERACTION_HPP
