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

            virtual bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const PROJECT::BASE::DATA::RectangleF& rv) noexcept = 0;

            virtual bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const PROJECT::BASE::DATA::Vector2F& rv) noexcept = 0;

            virtual bool check_intersection(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

            virtual bool check_intersection(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const PROJECT::BASE::DATA::RectangleF& rv) noexcept = 0;

            virtual std::vector<std::string> get_intersection_object_name(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const std::shared_ptr<INTERACTION>& rv) noexcept = 0;

            virtual std::vector<std::string> get_intersection_object_name(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                                  const PROJECT::BASE::DATA::RectangleF& rv) noexcept = 0;

            virtual ~IPhysics() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_PHYSICS_INTERFACE_HPP
