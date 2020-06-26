#pragma once
#include <vector>
#include "../object/drawable.hpp"
#include "./icollection.hpp"
#include "../object/identifiable.hpp"

namespace PROJECT::BASE::DATA
{
  class Vector2UI;
};

namespace PROJECT::COLLECTION
{
  class ILayout: public DRAWABLE, public PROJECT::COLLECTION::ICollection, public IDENTIFIABLE
  {
      public:
          virtual PROJECT::BASE::DATA::Vector2UI get_size() const noexcept = 0;

          virtual ~ILayout() = default;
  };
};