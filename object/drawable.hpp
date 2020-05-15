#pragma once

#include <string>

class DrawableObject;

class DRAWABLE
{
    public:
        virtual DrawableObject draw() const = 0;
        virtual void visible(bool flag) = 0;
        virtual bool is_visible() = 0;
		
		virtual ~DRAWABLE() = default;
};
