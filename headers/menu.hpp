#ifndef SFMLPROJECT_REBUILD_MENU_HPP
#define SFMLPROJECT_REBUILD_MENU_HPP

#include "../Interface/imenu.hpp"
#include <vector>

namespace PROJECT::MENU
{
	class Menu final : public PROJECT::MENU::IMenu
	{
		private:
			std::vector<std::shared_ptr<OBJECT>> _item;
			std::shared_ptr<OBJECT> _pointer;
			float item_step;
			float item_offset = 20;

		public:
			bool menu_configure(float X, float Y, float Width, float Height) noexcept override;

			void set_pointer(const std::shared_ptr<OBJECT>& pointer) noexcept;

			void add_item(const std::shared_ptr<OBJECT>& object) noexcept override;

			void step_forward() noexcept override;

			void step_back() noexcept override;

			void page_back() noexcept override;

			void page_forward() noexcept override;

			std::string selected_item() noexcept override;

			void reset() noexcept override;

			~Menu() = default;
	};
};

#endif //SFMLPROJECT_REBUILD_MENU_HPP
