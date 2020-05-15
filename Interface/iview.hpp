#pragma once

#include "../object/movable.hpp"
#include "../object/dynamic.hpp"
#include "../object/static.hpp"
#include "../object/interaction.hpp"

class IView: public MOVABLE, public DYNAMIC, public INTERACTION
{
    public:
        virtual void zoom(float zoom) = 0;
        virtual ~IView() = default;
};
