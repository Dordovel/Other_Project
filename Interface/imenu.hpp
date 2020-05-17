#pragma once
#include "./ilayout.hpp"
#include <map>
#include <memory>
#include "../object/object.hpp"

class IMenu
{
	public:
		virtual bool menu_configure() = 0;

		virtual void set_layout(const std::shared_ptr<ILayout>& layout) = 0;

		virtual void set_pointer(const std::shared_ptr<OBJECT>& pointer) = 0;

		virtual void add_item(const std::shared_ptr<OBJECT>& object) = 0;

		virtual void step_forward() = 0;

		virtual void step_back() = 0;

		virtual std::string selected_item() = 0;

		virtual ~IMenu() = default;
};
