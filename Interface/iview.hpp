#pragma once

#include "../object/movable.hpp"
#include "../object/dynamic.hpp"
#include "../object/static.hpp"
#include "../object/interaction.hpp"
#include "../object/modifiable.hpp"

class IView: public MOVABLE, public DYNAMIC, public INTERACTION, public MODIFIABLE
{
    public:
        virtual void zoom(float zoom) = 0;
        virtual Vector2F get_size() const = 0;
		virtual void set_size(const Vector2F& size) = 0;
		virtual void set_size(float x, float y) = 0;
        virtual ~IView() = default;
};
