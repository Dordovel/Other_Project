#include "../headers/physics.hpp"
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"
#include "../struct/static_object_collection.hpp"

namespace PROJECT::PHYSICS
{

	bool Physics::check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		return this->check_intersection(lv, rv->get_global_bounds());
	}

	bool Physics::check_intersection(const std::shared_ptr<INTERACTION>& lv, const PROJECT::BASE::DATA::RectangleF& rv) noexcept
	{
		return lv->collision(rv);
	}

	bool Physics::check_intersection(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
															const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		return this->check_intersection(lv, rv->get_global_bounds());
	}

	bool Physics::check_intersection(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
															const PROJECT::BASE::DATA::RectangleF& rv) noexcept
	{
		auto collisionPoint = lv->get_objects(rv);
		return !collisionPoint.empty();
	}

	std::vector<std::string> Physics::get_intersection_object_name(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
															const std::shared_ptr<INTERACTION>& rv) noexcept
	{
		return this->get_intersection_object_name(lv, rv->get_global_bounds());
	}

	std::vector<std::string> Physics::get_intersection_object_name(const std::shared_ptr<PROJECT::COLLECTION::ICollection>& lv,
															const PROJECT::BASE::DATA::RectangleF& rv) noexcept
	{
		std::vector<std::string> result;
		result.reserve(2);

		auto collisionPoint = lv->get_objects(rv);

		for(auto&& [key, points] : collisionPoint)
		{
			for(auto var : points)
			{
				if (var.intersects(rv))
				{
					result.emplace_back(key);
				}
			}	
		}

		return result;
	}
};
