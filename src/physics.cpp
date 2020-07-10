#include "../headers/physics.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"
#include "../struct/static_object_collection.hpp"

namespace PROJECT::PHYSICS
{
	bool Physics::check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		if(!lv || !rv) return false;
		return lv->collision(rv);
	}

	std::vector<std::string> Physics::get_collision_object(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
                                                           const std::shared_ptr<INTERACTION>& rv) noexcept
	{
	    std::vector<std::string> result;
	    result.reserve(2);

		PROJECT::BASE::DATA::RectangleF bounds = rv->get_global_bounds();

		auto collisionPoint = lv->get_objects(rv->get_global_bounds());

		for(auto&& [key, points] : collisionPoint)
		{
			for(auto var : points)
			{
				if (var.intersects(bounds))
				{
					result.emplace_back(key);
				}
			}	
		}

		return result;
	}

    bool Physics::check_collision(const std::shared_ptr <PROJECT::COLLECTION::ICollection>& lv,
                                  const std::shared_ptr <INTERACTION>& rv) noexcept
    {
        PROJECT::BASE::DATA::RectangleF bounds = rv->get_global_bounds();

        auto collisionPoint = lv->get_objects(rv->get_global_bounds());

        for(auto&& [key, points] : collisionPoint)
        {
            for(auto var : points)
            {
                if (var.intersects(bounds))
                {
                    return true;
                }
            }
        }

        return false;
    }
};
