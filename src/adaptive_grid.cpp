#include "../headers/adaptive_grid.hpp"
#include "../struct/rect_object.hpp"
#include <cmath>

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

		float offsetY = bounds.height + this->_item_offset;

		float offsetX = bounds.width + this->_item_offset;

		int countY = std::ceil(this->_height / offsetY);

		int countX = std::ceil(this->_width / offsetX);

		size_t elementOnPage = countX * countY;

		if(array.size() > elementOnPage)
		{
			return array.size() - elementOnPage;
		}

		float y;

		float x;

		int completeY;
		int completeX;

		y = this->_y;
		x = this->_x;
		completeY = 0;
		completeX = 1;


		for(auto& value : array)
		{
			if(completeY >= countY)
			{
				completeY = 0;
				x = this->_x+ (completeX * offsetX);
				y = this->_y;

				++completeX;
			}

			value->set_position(x, y);
			y += offsetY;

			++completeY;
		}

		return 0;
	}
};
