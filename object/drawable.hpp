#pragma once

#include <string>

class DrawableObject;

class DRAWABLE
{
    public:
        virtual DrawableObject draw() const noexcept = 0;
        virtual void visible(bool flag) noexcept = 0;
        virtual bool is_visible() noexcept = 0;
		
		virtual ~DRAWABLE() = default;
};
