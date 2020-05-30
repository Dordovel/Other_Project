#pragma once

#include <vector>
#include <map>

enum class CollectionObject;
class RectangleF;

class ICollection
{
    public:
        virtual std::map<CollectionObject, std::vector<RectangleF>> get_objects(const RectangleF& rectangleF) const noexcept = 0;
        virtual ~ICollection() = default;
};
