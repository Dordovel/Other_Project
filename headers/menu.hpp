#pragma once 

#include "../Interface/imenu.hpp"
#include <vector>

class Menu : public IMenu
{
	private:
		std::vector<std::shared_ptr<OBJECT>> _item;
		std::shared_ptr<ILayout> _layout;
		std::shared_ptr<OBJECT> _pointer;
		float item_step;

	public:
		bool menu_configure() override;

		void set_layout(const std::shared_ptr<ILayout>& layout) override;

		void set_pointer(const std::shared_ptr<OBJECT>& pointer) override;

		void add_item(const std::shared_ptr<OBJECT>& object) override;

		void step_forward() override;

		void step_back() override;

		std::string selected_item() override;

		void reset() override;

		~Menu() = default;
};
