#ifndef SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP

#include "./icollection.hpp"
#include "../object/interaction.hpp"

namespace PROJECT::PHYSICS
{
    class IPhysics
    {
        public:
            virtual bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

            virtual std::vector<std::string> get_collision_object(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

            virtual bool check_collision(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                          const std::shared_ptr<INTERACTION>& rv) noexcept = 0;
            virtual ~IPhysics() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP