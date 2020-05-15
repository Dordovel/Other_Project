#include <iostream>
#include "../headers/physics.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/vectorobject.hpp"

bool Physics::check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv)
{
    if(!lv || !rv) return false;
    return lv->collision(rv);
}

bool Physics::check_collision(const std::shared_ptr<ICollection>& lv,
								const std::shared_ptr<INTERACTION>& rv,
								std::initializer_list<CollectionObject> object)
{
    RectangleF bounds = rv->get_global_bounds();

    auto collisionPoint = lv->get_objects(rv->get_global_bounds());

    for(auto&& [key, points] : collisionPoint)
    {
		for(const auto& var : object)
		{	
			if(key == var)
			{
				for(auto var : points)
				{
					if (var.intersects(bounds))
					{
						return true;
					}
				}	
			}
		}
    }

    return false;
}
