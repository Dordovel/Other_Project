#pragma once
#include <map>
#include <memory>
#include "../object/object.hpp"
#include "./ilayout.hpp"

class IMenu
{
	public:
		virtual bool menu_configure() noexcept = 0;

		virtual void set_layout(const std::shared_ptr<ILayout>& layout) noexcept = 0;

		virtual void set_pointer(const std::shared_ptr<OBJECT>& pointer) noexcept = 0;

		virtual void add_item(const std::shared_ptr<OBJECT>& object) noexcept = 0;

		virtual void step_forward() noexcept = 0;

		virtual void step_back() noexcept = 0;

		virtual std::string selected_item() noexcept = 0;

		virtual void reset() noexcept = 0;

		virtual ~IMenu() = default;
};
