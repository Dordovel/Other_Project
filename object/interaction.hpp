#pragma once

#include "./static.hpp"
#include <memory>

class Vector2F;

class INTERACTION : public  STATIC
{
    public:
        virtual bool collision(const std::shared_ptr<INTERACTION>& object) = 0;
        virtual bool collision(const Vector2F& object) = 0;
        virtual ~INTERACTION() = default;
};
