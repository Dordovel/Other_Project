#pragma once

#include "../Interface/icompass.hpp"

class Compass : public ICompass
{
    unsigned int _lastPositionX;
    unsigned int _lastPositionY;

    unsigned int _mapSizeX;
    unsigned int _mapSizeY;

    public:

        Compass(unsigned int mapSizeX, unsigned int mapSizeY);
        CompassSide get_compass_side(unsigned int x, unsigned int y) noexcept override;

        ~Compass() = default;
};
