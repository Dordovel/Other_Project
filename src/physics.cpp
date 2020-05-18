#include "../headers/physics.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/colllectionobject.hpp"

bool Physics::check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv)
{
    if(!lv || !rv) return false;
    return lv->collision(rv);
}

CollectionObject Physics::check_collision(const std::shared_ptr<ICollection>& lv,
								const std::shared_ptr<INTERACTION>& rv)
{
    RectangleF bounds = rv->get_global_bounds();

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

    return CollectionObject::NONE;
}
