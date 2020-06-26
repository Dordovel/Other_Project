#include "../headers/physics.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/collectionobject.hpp"

namespace PROJECT::PHYSICS
{
	bool Physics::check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		if(!lv || !rv) return false;
		return lv->collision(rv);
	}

	std::string Physics::check_collision(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
		  const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		PROJECT::BASE::DATA::RectangleF bounds = rv->get_global_bounds();

		auto collisionPoint = lv->get_objects(rv->get_global_bounds());

		for(auto&& [key, points] : collisionPoint)
		{
			for(auto var : points)
			{
				if (var.intersects(bounds))
				{
					return key;
				}
			}	
		}

		return PROJECT::COLLECTION::CollectionObject::NONE;
	}
};
