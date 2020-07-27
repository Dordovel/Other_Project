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
	void VerticalGrid::init(float x, float y, float width, float height) noexcept
	{
		this->_x = x;
		this->_y = y;
		this->_width = width;
		this->_height = height;
	}


	void VerticalGrid::set_align(PROJECT::GRID::VERTICAL::GridAlign align) noexcept
	{
		this->_align = align;
	}
	
	size_t VerticalGrid::sort(const std::vector<std::shared_ptr<OBJECT>>& array) noexcept
	{
		PROJECT::BASE::DATA::RectangleF bounds = array.front()->get_global_bounds();

		float offsetY = bounds.height + this->_item_offset;

		size_t elementOnPage = std::ceil(this->_height / offsetY);

		if(array.size() > elementOnPage)
		{
			return array.size() - elementOnPage;
		}

		float y = this->_y;
		float x = this->_x + offset(this->_align, this->_width, bounds.width);

		for(const auto& value : array)
		{
			value->set_position(x, y);

			y += offsetY;
								
		}

		return 0;
	}
};
