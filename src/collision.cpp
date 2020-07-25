#include "../headers/collision.hpp"
#include "../struct/static_object_collection.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/side.hpp"

namespace PROJECT::COLLISION
{

	namespace 
	{ 
		void positioning(const PROJECT::BASE::DATA::RectangleF rect,
							const std::shared_ptr<DYNAMIC>& circleRight,
							const std::shared_ptr<DYNAMIC>& circleLeft,
							const std::shared_ptr<DYNAMIC>& circleUp,
							const std::shared_ptr<DYNAMIC>& circleDown)
		{
			circleRight->set_position((rect.left + rect.width), (rect.top + (rect.height / 2)));
			circleLeft->set_position(rect.left, (rect.top + (rect.height / 2)));
			circleUp->set_position((rect.left + (rect.width / 2)), rect.top);
			circleDown->set_position((rect.left + (rect.width / 2)), (rect.top + rect.height));
		}
	};



	Collision::Collision(std::shared_ptr<OBJECT>&& rail)
	{
		this->_circleUp = rail->clone();
		this->_circleLeft = rail->clone();
		this->_circleRight = rail->clone();
		this->_circleDown = rail->clone();
	}

	Collision::~Collision()
	{
	}

	std::pair<PROJECT::MOVE::Side, std::string>
	    Collision::check_object_collision(const std::shared_ptr<INTERACTION>& lv,
                                            const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		BASE::DATA::RectangleF rect;
        std::pair<PROJECT::MOVE::Side, std::string> result = {MOVE::Side::NONE, ""};

		if(this->_physics.check_intersection(lv, rv))
		{
			rect = lv->get_global_bounds();

			positioning(rect, this->_circleRight, this->_circleLeft, this->_circleUp, this->_circleDown);

			if(this->_physics.check_intersection(rv, this->_circleRight))
			{
				result = {MOVE::Side::RIGHT, ""};
			}
			
			if(this->_physics.check_intersection(rv, this->_circleLeft))
			{
				result = {MOVE::Side::LEFT, ""};
			}

			if(this->_physics.check_intersection(rv, this->_circleUp))
			{
				result = {MOVE::Side::UP, ""};
			}

			if(this->_physics.check_intersection(rv, this->_circleDown))
			{
			    result = {MOVE::Side::DOWN, ""};
			}

		}

		return result;
	}

	std::vector<std::pair<PROJECT::MOVE::Side, std::string>>
	    Collision::check_object_collision(const std::shared_ptr<PROJECT::COLLECTION::ILayout>& lv,
	                                        const std::shared_ptr<INTERACTION>& rv ) noexcept
	{
		BASE::DATA::RectangleF rect;
        std::vector<std::pair<PROJECT::MOVE::Side, std::string>> result;

		auto&& collisionObjectList = this->_physics.get_collision_object(lv, rv);

        if (!collisionObjectList.empty())
        {
            rect = rv->get_global_bounds();

            positioning(rect,
                this->_circleRight,
                this->_circleLeft,
                this->_circleUp,
                this->_circleDown);


			auto&& collection = this->_physics.get_collision_object(lv, this->_circleRight);
            if (!collection.empty())
            {
                result.emplace_back(MOVE::Side::RIGHT, collection.at(0));
            }

			collection = this->_physics.get_collision_object(lv, this->_circleLeft);
            if (!collection.empty())
            {
                result.emplace_back(MOVE::Side::LEFT, collection.at(0));
            }

			collection = this->_physics.get_collision_object(lv, this->_circleUp);
            if (!collection.empty())
            {
                result.emplace_back(MOVE::Side::UP, collection.at(0));
            }

			collection = this->_physics.get_collision_object(lv, this->_circleDown);
            if (!collection.empty())
            {
                result.emplace_back(MOVE::Side::DOWN, collection.at(0));
            }
        }

		return result;
	}
};
