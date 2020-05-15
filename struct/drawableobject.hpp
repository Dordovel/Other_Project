#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <memory>

class DrawableObject
{
    public:
        std::shared_ptr<sf::Drawable> object;
};