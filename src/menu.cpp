#include "../headers/menu.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"
#include "../id.hpp"

namespace
{
	using namespace PROJECT::BASE::DATA;

	Vector2F get_object_size(const std::shared_ptr<STATIC>& layout) noexcept
	{
		RectangleF layoutRect = layout->get_global_bounds();
		return {layoutRect.width, layoutRect.height};
	}
};


namespace PROJECT::MENU
{
	bool Menu::menu_configure(float X, float Y, float Width, float Height) noexcept
	{
		size_t size = 0;

		for(const auto& object : this->_item)
		{
			size += get_object_size(object).y;
		}

		if(size < Height)
		{
			this->item_step = ((Height - size) / this->_item.size());
			float pointerX = X + (Width / 2);
			float pointerY = Y + this->item_offset;

			for(const auto& object : this->_item)
			{
				object->set_position(pointerX, pointerY);
				pointerY += this->item_step;
			}

			PROJECT::BASE::DATA::Vector2F firstElementPosition = (*this->_item.begin())->get_position();
			PROJECT::BASE::DATA::RectangleF pointerBounds = this->_pointer->get_global_bounds();
			this->_pointer->set_position(pointerX - (pointerBounds.width * 2), 
											firstElementPosition.y + (pointerBounds.height / 2));

			return true;
		}

		return false;
	}

	void Menu::set_pointer(const std::shared_ptr<OBJECT>& pointer) noexcept
	{
		this->_pointer = pointer;
	}

	void Menu::add_item(const std::shared_ptr<OBJECT>& object) noexcept
	{
		this->_item.emplace_back(object);
	}

	void Menu::step_forward() noexcept
	{
		std::string selected_item_id = this->selected_item();

		if(selected_item_id != this->_item.back()->get_id())
		{
			PROJECT::BASE::DATA::Vector2F oldPosition = this->_pointer->get_position();
			this->_pointer->set_position(oldPosition.x, oldPosition.y + this->item_step);
		}
	}

	void Menu::step_back() noexcept
	{	
		std::string selected_item_id = this->selected_item();

		if(selected_item_id != this->_item.front()->get_id())
		{
			PROJECT::BASE::DATA::Vector2F oldPosition = this->_pointer->get_position();
			this->_pointer->set_position(oldPosition.x, oldPosition.y - this->item_step);
		}
	}

	std::string Menu::selected_item() noexcept
	{
		PROJECT::BASE::DATA::Vector2F itemPosition;
		PROJECT::BASE::DATA::Vector2F pointerPosition = this->_pointer->get_position();
		PROJECT::BASE::DATA::RectangleF itemRect;

		for (const auto& object : this->_item)
		{
			itemPosition = object->get_position();
			itemRect = object->get_global_bounds();

			if(pointerPosition.y > itemPosition.y - itemRect.height
				&& pointerPosition.y < itemPosition.y + itemRect.height)
			{
				return object->get_id();
			}
		}

		return "";
	}


	void Menu::reset() noexcept
	{
		this->_item.clear();
		this->_layout = nullptr;
	}
};
