#ifndef SFMLPROJECT_REBUILD_CHEST_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_CHEST_INTERFACE_HPP

#include "../object/object.hpp"
#include "../graphicobject/isprite.hpp"
#include <vector>

namespace PROJECT::CHEST
{
    class IChest : virtual public PROJECT::BASE::GRAPHIC::ISprite
    {
        public:
            virtual void add_elements(std::shared_ptr<OBJECT>&& element) noexcept = 0;

            virtual void sort() noexcept = 0;

			virtual std::vector<std::shared_ptr<OBJECT>> get_elements_on_page() noexcept = 0;

			virtual void delete_element(size_t index) noexcept = 0;

			virtual size_t size() const noexcept = 0;

		    virtual int get_page()const noexcept = 0;

		    virtual void page_back() noexcept = 0;

		    virtual void page_forward() noexcept = 0;

			virtual bool is_empty() const noexcept = 0;

            virtual void set_page_position(float x, float y, float width, float height) noexcept = 0;

			virtual ~IChest() = default;
    };

};

#endif // SFMLPROJECT_REBUILD_CHEST_INTERFACE_HPP
