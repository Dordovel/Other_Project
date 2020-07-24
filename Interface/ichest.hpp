#ifndef SFMLPROJECT_REBUILD_CHEST_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_CHEST_INTERFACE_HPP

#include "../object/object.hpp"
#include "../graphicobject/isprite.hpp"

namespace PROJECT::CHEST
{
    class IChest : virtual public PROJECT::BASE::GRAPHIC::ISprite
    {
        public:
            virtual void add_elements(std::shared_ptr<OBJECT>&& element) noexcept = 0;

			virtual std::shared_ptr<OBJECT>& get_element(size_t index) noexcept = 0;

			virtual void delete_element(size_t index) noexcept = 0;

			virtual size_t size() const noexcept = 0;

			virtual bool is_empty() const noexcept = 0;

			virtual ~IChest() = default;
    };

};

#endif // SFMLPROJECT_REBUILD_CHEST_INTERFACE_HPP
