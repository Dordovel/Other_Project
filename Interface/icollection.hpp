#ifndef SFMLPROJECT_REBUILD_COLLECTION_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_COLLECTION_INTERFACE_HPP

#include <vector>
#include <map>
#include <string>

namespace PROJECT::BASE::DATA
{
    class RectangleF;
};

namespace PROJECT::COLLECTION
{
    class ICollection
    {
        public:
            virtual std::map<std::string, std::vector<PROJECT::BASE::DATA::RectangleF>> get_objects(PROJECT::BASE::DATA::RectangleF rectangleF) const noexcept = 0;
            virtual ~ICollection() = default;
    };
};

#endif //SFMLPROJECT_REBUILD_COLLECTION_INTERFACE_HPP
