#ifndef SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP

#include "./icollection.hpp"
#include "../object/interaction.hpp"

namespace PROJECT::PHYSICS
{
    class IPhysics
    {
        public:
            virtual bool check_intersection(const INTERACTION* const lv, const INTERACTION* const rv) noexcept = 0;

            virtual bool check_intersection(const INTERACTION* const lv, PROJECT::BASE::DATA::RectangleF rv) noexcept = 0;

            virtual bool check_intersection(const INTERACTION* const lv, PROJECT::BASE::DATA::Vector2F rv) noexcept = 0;

            virtual bool check_intersection(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  const INTERACTION* const rv) noexcept = 0;

            virtual bool check_intersection(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  PROJECT::BASE::DATA::RectangleF rv) noexcept = 0;

            virtual std::vector<std::string> get_intersection_object_name(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  const INTERACTION* const rv) noexcept = 0;

            virtual std::vector<std::string> get_intersection_object_name(const PROJECT::COLLECTION::ICollection* const lv,
                                                                  PROJECT::BASE::DATA::RectangleF rv) noexcept = 0;

            virtual ~IPhysics() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP
