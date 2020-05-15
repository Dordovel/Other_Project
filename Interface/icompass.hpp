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


class ICompass
{
    public:
        virtual ~ICompass() = default;
        virtual CompassSide get_compass_side(unsigned int x, unsigned int y) noexcept = 0;
};
