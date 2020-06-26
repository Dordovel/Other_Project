#pragma once

#include "./identifiable.hpp"
#include "./movable.hpp"
#include "./drawable.hpp"
#include "./modifiable.hpp"
#include "./di.hpp"

class OBJECT : public MOVABLE, 
				public DI,
				public IDENTIFIABLE, 
				public DRAWABLE, 
				public MODIFIABLE
{
    public:
        virtual ~OBJECT() = default;
};
