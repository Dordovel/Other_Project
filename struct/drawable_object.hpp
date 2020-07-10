#ifndef SFMLPROJECT_REBUILD_STRUCT_DRAWABLE_OBJECT_HPP
#define SFMLPROJECT_REBUILD_STRUCT_DRAWABLE_OBJECT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace PROJECT::BASE::DATA
{
    class DrawableObject
    {
        public:
            std::shared_ptr<sf::Drawable> object;

			~DrawableObject() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_STRUCT_DRAWABLE_OBJECT_HPP
