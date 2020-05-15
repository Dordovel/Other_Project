#pragma once

enum CompassSide
{
    North,
    North_West,
    North_East,
    East,
    South_East,
    South,
    South_West,
    West,
	Stand
};

class Vector2UI;

class Compass
{
    unsigned int _lastPositionX;
    unsigned int _lastPositionY;

    unsigned int _mapSizeX;
    unsigned int _mapSizeY;

    public:

        Compass(const Vector2UI& size);
        CompassSide get_compass_side(unsigned int x, unsigned int y) noexcept;

        ~Compass() = default;
};
