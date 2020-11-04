#include "../headers/collision.hpp"
#include "../struct/static_object_collection.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/side.hpp"

namespace PROJECT::COLLISION
{
	namespace 
	{ 
		class Unknown
		{
			public:

				static PROJECT::BASE::DATA::RectangleF circleRight;
				static PROJECT::BASE::DATA::RectangleF circleLeft;
				static PROJECT::BASE::DATA::RectangleF circleUp;
				static PROJECT::BASE::DATA::RectangleF circleDown;

				static void update(const PROJECT::BASE::DATA::RectangleF rect)
				{
					Unknown::circleRight.left = (rect.left + rect.width);
					Unknown::circleRight.top = (rect.top + (rect.height / 2));

					Unknown::circleLeft.left = rect.left;
					Unknown::circleLeft.top = (rect.top + (rect.height / 2));

					Unknown::circleUp.left = (rect.left + (rect.width / 2));
					Unknown::circleUp.top = rect.top;

					Unknown::circleDown.left = (rect.left + (rect.width / 2));
					Unknown::circleDown.top = (rect.top + rect.height);
				}
		};
		
		PROJECT::BASE::DATA::RectangleF Unknown::circleRight = {0, 0, 10, 10};
		PROJECT::BASE::DATA::RectangleF Unknown::circleLeft = {0, 0, 10, 10};
		PROJECT::BASE::DATA::RectangleF Unknown::circleUp = {0, 0, 10, 10};
		PROJECT::BASE::DATA::RectangleF Unknown::circleDown = {0, 0, 10, 10};
	}



	std::pair<PROJECT::MOVE::Side, std::string>
	    Collision::check_object_collision(const INTERACTION* const lv,
                                            const INTERACTION* const rv) noexcept
	{
        std::pair<PROJECT::MOVE::Side, std::string> result = {MOVE::Side::NONE, ""};

		if(this->_physics.check_intersection(lv, rv))
		{
			Unknown::update(lv->get_global_bounds());

			if(this->_physics.check_intersection(rv, Unknown::circleRight))
			{
				result = {MOVE::Side::RIGHT, ""};
			}
			
			if(this->_physics.check_intersection(rv, Unknown::circleLeft))
			{
				result = {MOVE::Side::LEFT, ""};
			}

			if(this->_physics.check_intersection(rv, Unknown::circleUp))
			{
				result = {MOVE::Side::UP, ""};
			}

			if(this->_physics.check_intersection(rv, Unknown::circleDown))
			{
			    result = {MOVE::Side::DOWN, ""};
			}

		}

		return result;
	}

	std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
	    Collision::check_object_collision(const PROJECT::COLLECTION::ILayout* const lv,
	                                        const INTERACTION* const rv ) noexcept
	{
        std::vector<std::pair<PROJECT::MOVE::Side, std::string>> result;
		std::vector<std::string> collection;

        if (this->_physics.check_intersection(lv, rv))
        {
            Unknown::update(rv->get_global_bounds());

			if(this->_physics.check_intersection(lv, Unknown::circleRight))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::circleRight);
                result.emplace_back(MOVE::Side::RIGHT, collection.at(0));
            }

			if(this->_physics.check_intersection(lv, Unknown::circleLeft))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::circleLeft);
                result.emplace_back(MOVE::Side::LEFT, collection.at(0));
            }

			if(this->_physics.check_intersection(lv, Unknown::circleUp))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::circleUp);
                result.emplace_back(MOVE::Side::UP, collection.at(0));
            }

			if(this->_physics.check_intersection(lv, Unknown::circleDown))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::circleDown);
                result.emplace_back(MOVE::Side::DOWN, collection.at(0));
            }
        }

		return result;
	}
};
