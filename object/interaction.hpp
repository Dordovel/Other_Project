#ifndef SFMLPROJECT_REBUILD_OBJECT_INTERACTION_HPP
#define SFMLPROJECT_REBUILD_OBJECT_INTERACTION_HPP

#include "./static.hpp"
#include <memory>

class INTERACTION : public STATIC
{
    public:
        virtual bool collision(const std::shared_ptr<INTERACTION>& object) noexcept = 0;
        virtual bool collision(const PROJECT::BASE::DATA::Vector2F& vec) noexcept = 0;
        virtual bool collision(const PROJECT::BASE::DATA::RectangleF& rect) noexcept = 0;
        virtual ~INTERACTION() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_INTERACTION_HPP
