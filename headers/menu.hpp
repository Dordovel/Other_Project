#ifndef SFMLPROJECT_REBUILD_MENU_HPP
#define SFMLPROJECT_REBUILD_MENU_HPP

#include "../Interface/imenu.hpp"
#include <vector>
#include "../struct/rect_object.hpp"
#include "../headers/vertical_grid.hpp"

namespace PROJECT::MENU
{
	class Menu final : public PROJECT::MENU::IMenu
	{
		private:
			std::vector<std::shared_ptr<OBJECT>> _item;
			PROJECT::BASE::DATA::RectangleF _pointer;
			float _item_step = 20;
			PROJECT::GRID::VERTICAL::VerticalGrid _verticalGrid;

		public:
			bool menu_configure(float X, float Y, float Width, float Height) noexcept override;

			void add_item(const std::shared_ptr<OBJECT>& object) noexcept override;

			void step_forward() noexcept override;

			void step_back() noexcept override;

			std::string selected_item() noexcept override;

			PROJECT::BASE::DATA::Vector2F get_pointer_position() noexcept;

			void reset() noexcept override;

			~Menu() = default;
	};
};

#endif //SFMLPROJECT_REBUILD_MENU_HPP
