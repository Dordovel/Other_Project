#include "../headers/menu.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"
#include <cmath>

namespace PROJECT::MENU
{
	Menu::Menu(float heightStep, float widthStep):_pointerLeft(0, 0, 10, 10),
													_pointerRight(0, 0, 10, 10),
													_heightStep(heightStep),
													_widthStep(widthStep){}

	bool Menu::menu_configure() noexcept
	{
		PROJECT::BASE::DATA::RectangleF firstElementPosition = this->_item.front();
		this->_heightStep = this->_heightStep + firstElementPosition.height;

		this->_pointerRight.left = (firstElementPosition.left + firstElementPosition.width) + (this->_pointerRight.width * 2);
		this->_pointerRight.top = firstElementPosition.top;

		this->_pointerLeft.left = (firstElementPosition.left - (this->_pointerLeft.width * 2)) - this->_pointerLeft.width;
		this->_pointerLeft.top = firstElementPosition.top;

		this->_index = 0;

		return true;
	}

	void Menu::add_item(PROJECT::BASE::DATA::RectangleF bounds) noexcept
	{
		this->_item.emplace_back(std::move(bounds));
	}

	void Menu::step_forward() noexcept
	{
		if(this->_index < (this->_item.size() - 1))
		{
			PROJECT::BASE::DATA::RectangleF pointer_pos = this->_item.at(this->_index + 1);

			this->_pointerRight.left = (pointer_pos.left + pointer_pos.width) + (this->_pointerRight.width * 2);
			this->_pointerRight.top = this->_pointerRight.top + this->_heightStep;

			this->_pointerLeft.left = (pointer_pos.left - (this->_pointerLeft.width * 2)) - this->_pointerLeft.width;
			this->_pointerLeft.top = this->_pointerLeft.top + this->_heightStep;

			++this->_index;
		}
	}

	void Menu::step_back() noexcept
	{	
		if(this->_index > 0)
		{
			PROJECT::BASE::DATA::RectangleF pointer_pos = this->_item.at(this->_index - 1);

			this->_pointerRight.left = (pointer_pos.left + pointer_pos.width) + (this->_pointerRight.width * 2);
			this->_pointerRight.top = this->_pointerRight.top - this->_heightStep;

			this->_pointerLeft.left = (pointer_pos.left - (this->_pointerLeft.width * 2)) - this->_pointerLeft.width;
			this->_pointerLeft.top = this->_pointerLeft.top - this->_heightStep;

			--this->_index;
		}
	}

	int Menu::selected_item() noexcept
	{
		return this->_index;
	}

	void Menu::reset() noexcept
	{
		this->_item.clear();
	}

	std::array<PROJECT::BASE::DATA::Vector2F, 2> Menu::get_pointer_position() noexcept
	{
		using namespace PROJECT::BASE::DATA;

		return {
					Vector2F{this->_pointerLeft.left, this->_pointerLeft.top},
					Vector2F{this->_pointerRight.left, this->_pointerRight.top}
				};
	}
};
