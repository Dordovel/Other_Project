#ifndef SFMLPROJECT_REBUILD_CHEST_HPP
#define SFMLPROJECT_REBUILD_CHEST_HPP

#include "../Interface/ichest.hpp"
#include "../graphicobject/sprite.hpp"
#include <vector>

namespace PROJECT::CHEST
{
    class Chest : public PROJECT::CHEST::IChest,
					public PROJECT::BASE::GRAPHIC::Sprite
    {
		private:
			std::vector<std::shared_ptr<OBJECT>> _elements;

        public:
            void add_elements(std::shared_ptr<OBJECT>&& element) noexcept;

			std::shared_ptr<OBJECT>& get_element(size_t index) noexcept;

			void delete_element(size_t index) noexcept;

			size_t size() const noexcept;

			bool is_empty() const noexcept;

			explicit Chest(const PROJECT::DATABASE::DataBaseResult& data);
			
			Chest(const Chest&) = default;

			Chest(Chest&&) = default;

			Chest& operator= (Chest&&) = default;

			Chest& operator= (const Chest&) = default;

			~Chest() = default;
    };

};

#endif // SFMLPROJECT_REBUILD_CHEST_HPP
