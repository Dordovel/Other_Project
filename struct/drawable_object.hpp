#ifndef SFMLPROJECT_REBUILD_STRUCT_DRAWABLE_OBJECT_HPP
#define SFMLPROJECT_REBUILD_STRUCT_DRAWABLE_OBJECT_HPP

#include <SFML/Graphics/Drawable.hpp>

namespace PROJECT::BASE::DATA
{
    class DrawableObject
    {
        public:
			const sf::Drawable& object;

			~DrawableObject() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_STRUCT_DRAWABLE_OBJECT_HPP
