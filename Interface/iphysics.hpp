#pragma once
#include "./icollection.hpp"
#include "../object/interaction.hpp"

class Vector2F;
class RectangleF;

class IPhysics
{
    public:
        virtual bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) = 0;

        virtual bool check_collision(const std::shared_ptr<ICollection>& lv,
										const std::shared_ptr<INTERACTION>& rv,
										std::initializer_list<CollectionObject> object) = 0;

        virtual ~IPhysics() = default;
};
