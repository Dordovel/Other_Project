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

	float offset(MenuPosition position, float Width) noexcept
	{
		float center = Width / 2;

		if(position == MenuPosition::LEFT)
		{
			return center / 2;
		}

		if(position == MenuPosition::RIGHT)
		{
			return center + (center / 2);
		}

		return center;
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
		size_t size = 0;

		this->_pointer = {0, 0, 10, 10};

		float itemHeight = this->_item.front()->get_global_bounds().height;

		float itemOffset = itemHeight + this->_item_offset;
		
		int elementOnPage = Height / itemOffset;

		if(elementOnPage > this->_item.size())
		{
			this->_item_step = ((Height - size) / this->_item.size());
			float pointerX = X + offset(this->_position, Width);
			float pointerY = Y + this->_item_offset;

			for(const auto& object : this->_item)
			{
				object->set_position(pointerX, pointerY);
				pointerY += this->_item_step;
			}

			PROJECT::BASE::DATA::Vector2F firstElementPosition = (*this->_item.begin())->get_position();
			PROJECT::BASE::DATA::RectangleF pointerBounds = this->_pointer;
			this->_pointer.left = pointerX - (pointerBounds.width * 2);
			this->_pointer.top = firstElementPosition.y + (pointerBounds.height / 2);

			return true;
		}

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


	void Menu::set_position(MenuPosition position) noexcept
	{
		this->_position = position;
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
