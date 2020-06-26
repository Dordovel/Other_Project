#pragma once
#include <string>
#include "./rectobject.hpp"

namespace PROJECT::DATABASE
{
    struct DataBaseResult
    {
        std::string  rv;
        PROJECT::BASE::DATA::RectangleI rect;
    };
};
