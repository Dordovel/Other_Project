#ifndef SFMLPROJECT_REBUILD_STRUCT_DATABASE_RESULT_HPP
#define SFMLPROJECT_REBUILD_STRUCT_DATABASE_RESULT_HPP

#include <string>
#include "rect_object.hpp"

namespace PROJECT::DATABASE
{
    struct DataBaseResult
    {
        std::string  rv;
        PROJECT::BASE::DATA::RectangleI rect;
    };
};
#endif //SFMLPROJECT_REBUILD_STRUCT_DATABASE_RESULT_HPP
