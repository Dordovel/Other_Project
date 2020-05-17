#pragma once

#include "./identifiable.hpp"
#include "./movable.hpp"
#include "./interaction.hpp"
#include "./dynamic.hpp"
#include "./drawable.hpp"
#include "./modifiable.hpp"

class OBJECT : public MOVABLE, 
				public DYNAMIC, 
				public INTERACTION, 
				public IDENTIFIABLE, 
				public DRAWABLE, 
				public MODIFIABLE
{
    public:
        virtual ~OBJECT() = default;
};
