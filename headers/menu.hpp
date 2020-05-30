#pragma once 

#include "../Interface/imenu.hpp"
#include <vector>

class Menu final : public IMenu
{
	private:
		std::vector<std::shared_ptr<OBJECT>> _item;
		std::shared_ptr<ILayout> _layout;
		std::shared_ptr<OBJECT> _pointer;
		float item_step;

	public:
		bool menu_configure() noexcept override;

		void set_layout(const std::shared_ptr<ILayout>& layout) noexcept override;

		void set_pointer(const std::shared_ptr<OBJECT>& pointer) noexcept override;

		void add_item(const std::shared_ptr<OBJECT>& object) noexcept override;

		void step_forward() noexcept override;

		void step_back() noexcept override;

		std::string selected_item() noexcept override;

		void reset() noexcept override;

		~Menu() = default;
};
