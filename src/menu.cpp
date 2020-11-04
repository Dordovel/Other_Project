#include "../headers/menu.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"
#include <cmath>

namespace
{
	bool check_intersection(PROJECT::BASE::DATA::RectangleF lv,
							const OBJECT* const rv)
	{
		PROJECT::BASE::DATA::Vector2F rvPos = rv->get_position();
		PROJECT::BASE::DATA::RectangleF rvRect = rv->get_global_bounds();

		if( lv.top > rvPos.y - rvRect.height
			&& lv.top < rvPos.y + rvRect.height)
		{
			return true;
		}
		return false;
	}
};

namespace PROJECT::MENU
{
	Menu::Menu():_pointer(0, 0, 10, 10),
				_verticalGrid(PROJECT::GRID::VERTICAL::GridAlign::LEFT, this->_item_step){}

	bool Menu::menu_configure(float X, float Y, float Width, float Height) noexcept
	{
		this->_verticalGrid.init(X, Y, Width, Height);

		if(this->_verticalGrid.sort(this->_item) > 0)
			return false;

		PROJECT::BASE::DATA::RectangleF firstElementPosition = (*this->_item.begin())->get_global_bounds();
		this->_item_step = this->_item_step + firstElementPosition.height;

		PROJECT::BASE::DATA::RectangleF pointerBounds = this->_pointer;
		this->_pointer.left = (firstElementPosition.left + firstElementPosition.width) + (pointerBounds.width * 2);
		this->_pointer.top = firstElementPosition.top;

		this->_index = 0;

		return false;
	}

	void Menu::add_item(std::shared_ptr<OBJECT> object) noexcept
	{
		this->_item.emplace_back(std::move(object));
	}

	void Menu::step_forward() noexcept
	{
		if(this->_index < this->_item.size())
		{
			PROJECT::BASE::DATA::RectangleF pointer_pos = this->_item.at(this->_index + 1)->get_global_bounds();
			this->_pointer.left = (pointer_pos.left + pointer_pos.width) + (this->_pointer.width * 2);
			this->_pointer.top = this->_pointer.top + this->_item_step;

			++this->_index;
		}
	}

	void Menu::step_back() noexcept
	{	
		if(this->_index > 0)
		{
			PROJECT::BASE::DATA::RectangleF pointer_pos = this->_item.at(this->_index - 1)->get_global_bounds();
			this->_pointer.left = (pointer_pos.left + pointer_pos.width) + (this->_pointer.width * 2);
			this->_pointer.top = this->_pointer.top - this->_item_step;

			--this->_index;
		}
	}

	std::string Menu::selected_item() noexcept
	{
		return this->_item.at(this->_index)->get_id();
	}

	void Menu::reset() noexcept
	{
		this->_item.clear();
	}

	PROJECT::BASE::DATA::Vector2F Menu::get_pointer_position() noexcept
	{
		return {this->_pointer.left, this->_pointer.top};
	}
};
