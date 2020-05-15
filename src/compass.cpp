#include "../headers/compass.hpp"
#include "../struct/vectorobject.hpp"

Compass::Compass(const Vector2UI& size):_mapSizeX(size.x),
                                                                _mapSizeY(size.y),
                                                                _lastPositionX(size.x / 2),
                                                                _lastPositionY(size.y / 2)
{}


CompassSide Compass::get_compass_side(unsigned int x, unsigned int y) noexcept
{
    CompassSide result;

    if(x == this->_lastPositionX && y == this->_lastPositionY)
    { result = CompassSide::Stand; }

    if(x > this->_lastPositionX && y == this->_lastPositionY)
    { result = CompassSide::East; }

    if(x < this->_lastPositionX && y == this->_lastPositionY)
    { result = CompassSide::West; }

    if(y > this->_lastPositionY && x == this->_lastPositionX)
    { result = CompassSide::South; }

    if(y < this->_lastPositionY && x == this->_lastPositionX)
    { result = CompassSide::North; }


    if(x < this->_lastPositionX && y < this->_lastPositionY)
    { result = CompassSide::North_West; }

    if(y > this->_lastPositionY && x > this->_lastPositionX)
    { result = CompassSide::South_East; }

    if(y < this->_lastPositionY && x > this->_lastPositionX)
    { result = CompassSide::North_East; }

    if(y > this->_lastPositionY && x < this->_lastPositionX)
    { result = CompassSide::South_West; }

    this->_lastPositionX = x;
    this->_lastPositionY = y;

    return result;
}
