#ifndef SFMLPROJECT_REBUILD_CHEST_HPP
#define SFMLPROJECT_REBUILD_CHEST_HPP

#include "../Interface/ichest.hpp"
#include "../graphicobject/sprite.hpp"
#include <list>

namespace PROJECT::CHEST
{
    class Chest : public PROJECT::CHEST::IChest,
					public PROJECT::BASE::GRAPHIC::Sprite
    {
		private:
			std::vector<std::shared_ptr<OBJECT>> _elements;
			float _item_step;
			float _item_offset = 10;
			int _pageCout;
			size_t _elementOnPage;
			float _chestPageX;
			float _chestPageY;
			float _chestPageSizeHeight = 50;
			float _chestPageSizeWidth = 100;
			int _currentPage;
			size_t _begin;
			bool _isMod;

        public:
			void sort() noexcept override;

            void add_elements(std::shared_ptr<OBJECT>&& element) noexcept override;

			std::vector<std::shared_ptr<OBJECT>> get_elements_on_page() noexcept override;

			void delete_element(size_t index) noexcept override;

			size_t size() const noexcept override;

			bool is_empty() const noexcept override;

			int get_page() const noexcept override;

			void page_back() noexcept override;

			void page_forward() noexcept override;

            void set_page_position(float x, float y, float width, float height) noexcept override;

			explicit Chest(const PROJECT::DATABASE::DataBaseResult& data);
			
			Chest(const Chest&) = default;

			Chest(Chest&&) = default;

			Chest& operator= (Chest&&) = default;

			Chest& operator= (const Chest&) = default;

			~Chest() = default;
    };

};

#endif // SFMLPROJECT_REBUILD_CHEST_HPP
