#pragma once
#include <vector>
#include "../object/drawable.hpp"
#include "./icollection.hpp"
#include "../object/identifiable.hpp"

class Vector2UI;

class ILayout: public DRAWABLE, public ICollection, public IDENTIFIABLE
{
    public:
		virtual Vector2UI get_size() const = 0;

        virtual ~ILayout() = default;
};
