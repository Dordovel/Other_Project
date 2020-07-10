#ifndef SFMLPROJECT_REBUILD_LAYOUT_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_LAYOUT_INTERFACE_HPP

#include <vector>
#include "../object/drawable.hpp"
#include "./icollection.hpp"

namespace PROJECT::BASE::DATA
{
  class Vector2UI;
};

namespace PROJECT::COLLECTION
{
  class ILayout: public DRAWABLE, public PROJECT::COLLECTION::ICollection
  {
      public:
          virtual PROJECT::BASE::DATA::Vector2UI get_size() const noexcept = 0;

          virtual ~ILayout() = default;
  };
};
#endif //SFMLPROJECT_REBUILD_LAYOUT_INTERFACE_HPP