#pragma once

#include <vector>
#include <map>

namespace PROJECT::BASE::DATA
{
    class RectangleF;
};

namespace PROJECT::COLLECTION
{
    class ICollection
    {
        public:
            virtual std::map<std::string, std::vector<PROJECT::BASE::DATA::RectangleF>> get_objects(const PROJECT::BASE::DATA::RectangleF& rectangleF) const noexcept = 0;
            virtual ~ICollection() = default;
    };
};