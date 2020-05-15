#pragma once 
#include <SFML/Graphics/Color.hpp>

class Color : public sf::Color 
{
    public:
        Color(int red, int green, int blue):sf::Color(red, green, blue){};
};
