#pragma once

#include "../object/identifiable.hpp"
#include "../object/movable.hpp"
#include "../object/interaction.hpp"
#include "../object/dynamic.hpp"

class IOBJECT : public MOVABLE, public DYNAMIC, public INTERACTION, public IDENTIFIABLE
{
    public:
        virtual ~IOBJECT() = default;
};
