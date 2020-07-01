#include "../headers/collision.hpp"
#include "../struct/collectionobject.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/side.hpp"
#include "../graphicobject/circle.hpp"

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

	std::pair<PROJECT::MOVE::Side, std::string> Collision::check_object_collision(const std::shared_ptr<INTERACTION>& lv,
																					const std::shared_ptr<INTERACTION>& rv) noexcept
	{	
		BASE::DATA::RectangleF rect;
		MOVE::Side side = MOVE::Side::NONE;

		if(this->_physics.check_intersection(lv, rv))
		{
			rect = lv->get_global_bounds();

			positioning(rect, this->_circleRight, this->_circleLeft, this->_circleUp, this->_circleDown);

			if(this->_physics.check_intersection(rv, this->_circleRight))
			{
				side = MOVE::Side::RIGHT;
			}
			
			if(this->_physics.check_intersection(rv, this->_circleLeft))
			{
				side = MOVE::Side::LEFT;
			}

			if(this->_physics.check_intersection(rv, this->_circleUp))
			{
				side = MOVE::Side::UP;
			}

			if(this->_physics.check_intersection(rv, this->_circleDown))
			{
				side = MOVE::Side::DOWN;
			}

		}

		return {side, ""};
	}

	std::pair<PROJECT::MOVE::Side, std::string> Collision::check_object_collision(const std::shared_ptr<PROJECT::COLLECTION::ILayout>& lv,
																				const std::shared_ptr<INTERACTION>& rv ) noexcept
	{
		using namespace PROJECT;

		BASE::DATA::RectangleF rect;
		MOVE::Side side = MOVE::Side::NONE;

		std::string value;

		if(value = this->_physics.check_collision(lv, rv); value != COLLECTION::CollectionObject::NONE)
		{
			rect = rv->get_global_bounds();

			positioning(rect, this->_circleRight, this->_circleLeft, this->_circleUp, this->_circleDown);

			if(this->_physics.check_collision(lv, this->_circleRight) != COLLECTION::CollectionObject::NONE)
			{
				side = MOVE::Side::RIGHT;
			}
			
			if(this->_physics.check_collision(lv, this->_circleLeft) != COLLECTION::CollectionObject::NONE)
			{
				side = MOVE::Side::LEFT;
			}

			if(this->_physics.check_collision(lv, this->_circleUp) != COLLECTION::CollectionObject::NONE)
			{
				side = MOVE::Side::UP;
			}

			if(this->_physics.check_collision(lv, this->_circleDown) != COLLECTION::CollectionObject::NONE)
			{
				side = MOVE::Side::DOWN;
			}

		}	

		return {side, value};
	}
};
