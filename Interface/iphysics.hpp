#pragma once
#include "./icollection.hpp"
#include "../object/interaction.hpp"

namespace PROJECT::PHYSICS
{
    class IPhysics
    {
        public:
            virtual bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

            virtual std::string check_collision(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                            const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

            virtual ~IPhysics() = default;
    };
};