#pragma once
#include "./icollection.hpp"
#include "../object/interaction.hpp"

class Vector2F;
class RectangleF;
enum class CollectionObject;

class IPhysics
{
    public:
        virtual bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

        virtual CollectionObject check_collision(const std::shared_ptr<ICollection>& lv,
										const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

        virtual ~IPhysics() = default;
};
