#include "../headers/vertical_grid.hpp"
#include "../struct/rect_object.hpp"
#include <cmath>

namespace
{
	float offset(PROJECT::GRID::VERTICAL::GridAlign align, float width, float elementWidth)
	{
		if(align == PROJECT::GRID::VERTICAL::GridAlign::RIGHT)
		{
			return width - elementWidth;
		}

		if(align == PROJECT::GRID::VERTICAL::GridAlign::CENTER)
		{
			return (width / 2) - (elementWidth / 2);
		}

		return 0;
	}
};

namespace PROJECT::GRID::VERTICAL
{
	VerticalGrid::VerticalGrid (PROJECT::GRID::VERTICAL::GridAlign align, int offsetY)
	{
		this->_align = align;
		this->_item_offset = offsetY;
	}

	void VerticalGrid::init(float x, float y, float width, float height) noexcept
	{
		this->_x = x;
		this->_y = y;
		this->_width = width;
		this->_height = height;
	}
	
	size_t VerticalGrid::sort(const std::vector<std::shared_ptr<OBJECT>>& array) noexcept
	{
		PROJECT::BASE::DATA::RectangleF bounds;
		const std::size_t size = array.size();

		float posX = 0;
		float posY = this->_y;

		for(std::size_t i = 0; i < size; ++i)
		{
			bounds = array[i]->get_global_bounds();

			if(float height = (bounds.height + this->_item_offset);
					height < this->_height)
			{
				posX = this->_x + offset(this->_align, this->_width, bounds.width);

				if(i != 0)
					posY += height;

				array[i]->set_position(posX, posY);
			}
			else
			{
				return size - i;
			}
		}

		return 0;
	}
};
