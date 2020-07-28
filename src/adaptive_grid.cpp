#include "../headers/adaptive_grid.hpp"
#include "../struct/rect_object.hpp"
#include <cmath>
#include <iostream>

namespace PROJECT::GRID::ADAPTIVE
{
	void AdaptiveGrid::init(float x, float y, float width, float height) noexcept
	{
		this->_x = x;
		this->_y = y;
		this->_width = width;
		this->_height = height;
	}
	
	size_t AdaptiveGrid::sort(const std::vector<std::shared_ptr<OBJECT>>& array) noexcept
	{
		PROJECT::BASE::DATA::RectangleF bounds = array.front()->get_global_bounds();

		int countX = (this->_width / bounds.width);
		int countY = (this->_height / bounds.height);
		
		int freeSpaceX = this->_width - (bounds.width * countX);
		int freeSpaceY = this->_height - (bounds.height * countY);

		if(freeSpaceX == 0)
		{
			--countX;
			freeSpaceX = this->_width - (bounds.width * countX);
		}

		if(freeSpaceY == 0)
		{
			--countY;
			freeSpaceY = this->_height - (bounds.height * countY);
		}

		float offsetX = (float(freeSpaceX) / float(countX + 1));
		float offsetY = (float(freeSpaceY) / float(countY + 1));

		size_t elementOnPage = countX * countY;

		if(array.size() > elementOnPage)
		{
			return array.size() - elementOnPage;
		}

		float y = this->_y + offsetY;
		float x = this->_x + offsetX;

		float X = 0;

		for (const auto& value : array)
		{
			if(X == countX)
			{
				x = this->_x + offsetX;
				y = (y + offsetY) + (bounds.height);

				X = 0;
			}

			value->set_position(x, y);
			x = (x + offsetX) + (bounds.width);

			++X;
		}

		return 0;
	}
};
