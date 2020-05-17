#include "../headers/menu.hpp"
#include "../struct/rectobject.hpp"
#include "../id.hpp"
#include <iostream>

bool Menu::menu_configure()
{
	Vector2UI layoutSize = this->_layout->get_size();
	
	size_t size = 0;

	for(const auto& var: this->_item)
	{
		size += var->get_global_bounds().height;
	}

	if(size < layoutSize.y)
	{
		this->item_step = (layoutSize.y - size) / this->_item.size();

		Vector2UI layoutCenter = { (layoutSize.x / 2), (layoutSize.y / 2) };
		float x_center = layoutCenter.x;
		float y_pos = 0;

		for(const auto& var : this->_item)
		{
			var->set_position(x_center, y_pos);
			y_pos += this->item_step + var->get_global_bounds().height;
		}

		return true;
	}

	return false;
}

void Menu::set_layout(const std::shared_ptr<ILayout>& layout)
{
	this->_layout = layout;
}

void Menu::set_pointer(const std::shared_ptr<OBJECT>& pointer)
{
	this->_pointer = pointer;
}

void Menu::add_item(const std::shared_ptr<OBJECT>& object)
{
	this->_item.push_back(object);
}

void Menu::step_forward()
{
}

void Menu::step_back()
{
}

std::string Menu::selected_item()
{
}
