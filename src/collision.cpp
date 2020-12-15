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

				static inline PROJECT::BASE::DATA::RectangleF rectangleRight = {0, 0, 0, 0};
				static inline PROJECT::BASE::DATA::RectangleF rectangleLeft = {0, 0, 0, 0};
				static inline PROJECT::BASE::DATA::RectangleF rectangleUp = {0, 0, 0, 0};
				static inline PROJECT::BASE::DATA::RectangleF rectangleDown = {0, 0, 0, 0};

				static inline PROJECT::BASE::DATA::RectangleF rectangleRightUp = {0, 0, 0, 0};
				static inline PROJECT::BASE::DATA::RectangleF rectangleLeftUp = {0, 0, 0, 0};
				static inline PROJECT::BASE::DATA::RectangleF rectangleLeftDown = {0, 0, 0, 0};
				static inline PROJECT::BASE::DATA::RectangleF rectangleRightDown = {0, 0, 0, 0};

				static void update(const PROJECT::BASE::DATA::RectangleF rect)
				{
					Unknown::rectangleRight = {0, 0, 10, 10};
					Unknown::rectangleLeft = {0, 0, 10, 10};
					Unknown::rectangleUp = {0, 0, 10, 10};
					Unknown::rectangleDown = {0, 0, 10, 10};

					Unknown::rectangleRight.left = (rect.left + rect.width);
					Unknown::rectangleRight.top = (rect.top + (rect.height / 2));

					Unknown::rectangleLeft.left = rect.left;
					Unknown::rectangleLeft.top = (rect.top + (rect.height / 2));

					Unknown::rectangleUp.left = (rect.left + (rect.width / 2));
					Unknown::rectangleUp.top = rect.top;

					Unknown::rectangleDown.left = (rect.left + (rect.width / 2));
					Unknown::rectangleDown.top = (rect.top + rect.height);
				}

				static void update(const PROJECT::BASE::DATA::RectangleF rect, float radius)
				{

					float width = radius - rect.width;
					float height = radius - rect.height;

					Unknown::rectangleRight = {0, 0, width, rect.height};
					Unknown::rectangleLeft = {0, 0, width, rect.height};
					Unknown::rectangleUp = {0, 0, rect.width, height};
					Unknown::rectangleDown = {0, 0, rect.width, height};

					Unknown::rectangleRightUp = {0, 0, (width - 2), (height - 2)};
					Unknown::rectangleLeftUp = {0, 0, (width - 2), (height - 2)};
					Unknown::rectangleLeftDown = {0, 0, (width - 2), (height - 2)};
					Unknown::rectangleRightDown = {0, 0, (width - 2), (height - 2)};


					Unknown::rectangleRight.left = (rect.left + rect.width);
					Unknown::rectangleRight.top = (rect.top + (rect.height / 2));
					Unknown::rectangleLeft.left = rect.left;
					Unknown::rectangleLeft.top = (rect.top + (rect.height / 2));

					Unknown::rectangleUp.left = (rect.left + (rect.width / 2));
					Unknown::rectangleUp.top = rect.top;
					Unknown::rectangleDown.left = (rect.left + (rect.width / 2));
					Unknown::rectangleDown.top = (rect.top + rect.height);



					Unknown::rectangleRightUp.left = (rect.left + rect.width);
					Unknown::rectangleRightUp.top = (rect.top - rectangleRightUp.height);
					Unknown::rectangleLeftUp.left = rect.left;
					Unknown::rectangleLeftUp.top = (rect.top - rectangleLeftUp.height);

					Unknown::rectangleRightDown.left = (rect.left + rect.width);
					Unknown::rectangleRightDown.top = (rect.top + rectangleRightDown.height);
					Unknown::rectangleLeftDown.left = rect.left;
					Unknown::rectangleLeftDown.top = (rect.top + rectangleLeftDown.height);
				}
		};
	}



	std::pair<PROJECT::MOVE::Side, std::string>
	    Collision::check_object_collision(const INTERACTION* const lv,
                                            const INTERACTION* const rv,
											float radius) noexcept
	{
		if(radius == 0)
			return this->check_collision(lv, rv);
		else
			return this->check_collision(lv, rv, radius);
	}

	std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
	    Collision::check_object_collision(const PROJECT::COLLECTION::ILayout* const lv,
	                                        const INTERACTION* const rv,
											float radius) noexcept
	{
		if(radius == 0)
			return this->check_collision(lv, rv);
		else
			return this->check_collision(lv, rv, radius);
	}



std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
	Collision::check_collision(const PROJECT::COLLECTION::ILayout* const lv,
							const INTERACTION* const rv,
							float radius) noexcept
	{
        std::vector<std::pair<PROJECT::MOVE::Side, std::string>> result;
		std::vector<std::string> collection;

		Unknown::update(rv->get_global_bounds(), radius);

		if(this->_physics.check_intersection(lv, Unknown::rectangleRight))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleRight);
			result.emplace_back(MOVE::Side::RIGHT, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleLeft))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleLeft);
			result.emplace_back(MOVE::Side::LEFT, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleUp))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleUp);
			result.emplace_back(MOVE::Side::UP, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleDown))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleDown);
			result.emplace_back(MOVE::Side::DOWN, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleRightUp))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleRightUp);
			result.emplace_back(MOVE::Side::RIGHT, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleLeftUp))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleLeftUp);
			result.emplace_back(MOVE::Side::LEFT, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleRightDown))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleRightDown);
			result.emplace_back(MOVE::Side::UP, collection[0]);
		}
		if(this->_physics.check_intersection(lv, Unknown::rectangleLeftDown))
		{
			collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleLeftDown);
			result.emplace_back(MOVE::Side::DOWN, collection[0]);
		}

		return result;
	}

std::pair<PROJECT::MOVE::Side, std::string>
	Collision::check_collision(const INTERACTION* const lv,
							const INTERACTION* const rv,
							float radius) noexcept
	{
        std::pair<PROJECT::MOVE::Side, std::string> result = {MOVE::Side::NONE, ""};

		Unknown::update(lv->get_global_bounds(), radius);

		if(this->_physics.check_intersection(rv, Unknown::rectangleRight))
		{
			result = {MOVE::Side::RIGHT, ""};
		}
		else if(this->_physics.check_intersection(rv, Unknown::rectangleLeft))
		{
			result = {MOVE::Side::LEFT, ""};
		}
		else if(this->_physics.check_intersection(rv, Unknown::rectangleUp))
		{
			result = {MOVE::Side::UP, ""};
		}
		else if(this->_physics.check_intersection(rv, Unknown::rectangleDown))
		{
			result = {MOVE::Side::DOWN, ""};
		}
		if(this->_physics.check_intersection(rv, Unknown::rectangleRightUp))
		{
			result = {MOVE::Side::RIGHT_UP, ""};
		}
		else if(this->_physics.check_intersection(rv, Unknown::rectangleLeftUp))
		{
			result = {MOVE::Side::LEFT_UP, ""};
		}
		else if(this->_physics.check_intersection(rv, Unknown::rectangleRightDown))
		{
			result = {MOVE::Side::RIGHT_DOWN, ""};
		}
		else if(this->_physics.check_intersection(rv, Unknown::rectangleLeftDown))
		{
			result = {MOVE::Side::LEFT_DOWN, ""};
		}

		return result;
	}

std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
	Collision::check_collision(const PROJECT::COLLECTION::ILayout* const lv,
							const INTERACTION* const rv) noexcept
	{
        std::vector<std::pair<PROJECT::MOVE::Side, std::string>> result;
		std::vector<std::string> collection;

        if (this->_physics.check_intersection(lv, rv))
        {
            Unknown::update(rv->get_global_bounds());

			if(this->_physics.check_intersection(lv, Unknown::rectangleRight))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleRight);
                result.emplace_back(MOVE::Side::RIGHT, collection[0]);
            }

			if(this->_physics.check_intersection(lv, Unknown::rectangleLeft))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleLeft);
                result.emplace_back(MOVE::Side::LEFT, collection[0]);
            }

			if(this->_physics.check_intersection(lv, Unknown::rectangleUp))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleUp);
                result.emplace_back(MOVE::Side::UP, collection[0]);
            }

			if(this->_physics.check_intersection(lv, Unknown::rectangleDown))
            {
				collection = this->_physics.get_intersection_object_name(lv, Unknown::rectangleDown);
                result.emplace_back(MOVE::Side::DOWN, collection[0]);
            }
        }

		return result;
	}

std::pair<PROJECT::MOVE::Side, std::string>
	Collision::check_collision(const INTERACTION* const lv,
							const INTERACTION* const rv) noexcept
	{
        std::pair<PROJECT::MOVE::Side, std::string> result = {MOVE::Side::NONE, ""};

		if(this->_physics.check_intersection(lv, rv))
		{
			Unknown::update(lv->get_global_bounds());

			if(this->_physics.check_intersection(rv, Unknown::rectangleRight))
			{
				result = {MOVE::Side::RIGHT, ""};
			}
			else if(this->_physics.check_intersection(rv, Unknown::rectangleLeft))
			{
				result = {MOVE::Side::LEFT, ""};
			}
			else if(this->_physics.check_intersection(rv, Unknown::rectangleUp))
			{
				result = {MOVE::Side::UP, ""};
			}
			else if(this->_physics.check_intersection(rv, Unknown::rectangleDown))
			{
			    result = {MOVE::Side::DOWN, ""};
			}
		}

		return result;
	}
};
