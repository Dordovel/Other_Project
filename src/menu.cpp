#include "../headers/menu.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"
#include <cmath>

namespace
{
	using namespace PROJECT::BASE::DATA;
	using namespace PROJECT::MENU;

	Vector2F get_object_size(const std::shared_ptr<STATIC>& layout) noexcept
	{
		RectangleF layoutRect = layout->get_global_bounds();
		return {layoutRect.width, layoutRect.height};
	}

	bool check_intersection(const PROJECT::BASE::DATA::RectangleF& lv,
							const std::shared_ptr<OBJECT>& rv)
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
	bool Menu::menu_configure(float X, float Y, float Width, float Height) noexcept
	{
		this->_verticalGrid.init(X, Y, Width, Height);

		this->_pointer = {0, 0, 10, 10};

		this->_verticalGrid.set_align(PROJECT::GRID::VERTICAL::GridAlign::LEFT);

		if(this->_verticalGrid.sort(this->_item) > 0)
			return false;

		PROJECT::BASE::DATA::RectangleF firstElementPosition = (*this->_item.begin())->get_global_bounds();
		this->_item_step = this->_item_step + firstElementPosition.height;

		PROJECT::BASE::DATA::RectangleF pointerBounds = this->_pointer;
		this->_pointer.left = (firstElementPosition.left + firstElementPosition.width) + (pointerBounds.width * 2);
		this->_pointer.top = firstElementPosition.top;


		return false;
	}

	void Menu::add_item(const std::shared_ptr<OBJECT>& object) noexcept
	{
		this->_item.emplace_back(object);
	}

	void Menu::step_forward() noexcept
	{
		if(!check_intersection(this->_pointer, this->_item.back()))
		{
			PROJECT::BASE::DATA::RectangleF oldPosition = this->_pointer;
			this->_pointer.left = oldPosition.left;
			this->_pointer.top = oldPosition.top + this->_item_step;
		}
	}

	void Menu::step_back() noexcept
	{	
		if(!check_intersection(this->_pointer, this->_item.front()))
		{
			PROJECT::BASE::DATA::RectangleF oldPosition = this->_pointer;
			this->_pointer.left = oldPosition.left;
			this->_pointer.top = oldPosition.top - this->_item_step;
		}
	}

	std::string Menu::selected_item() noexcept
	{
		for (const auto& object : this->_item)
		{
			if(check_intersection(this->_pointer, object))
			{
				return object->get_id();
			}
		}

		return "";
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
