#pragma once
#include <vector>
#include "../object/drawable.hpp"
#include "./icollection.hpp"
#include "../object/identifiable.hpp"

class Vector2F;
class RectangleF;


class IMap: public DRAWABLE, public ICollection, public IDENTIFIABLE
{
    public:
        virtual unsigned int get_map_size_x() const = 0;
        virtual unsigned int get_map_size_y() const = 0;

        virtual ~IMap() = default;
};
