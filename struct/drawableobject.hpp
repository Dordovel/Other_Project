#pragma once

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
