#pragma once
#include "../Interface/iphysics.hpp"
#include "../Interface/igamemap.hpp"
#include "../object/interaction.hpp"

class Physics: public IPhysics
{
    public:

        bool check_intersection(const std::shared_ptr<INTERACTION>& lv, const std::shared_ptr<INTERACTION>& rv) override;

        bool check_collision(const std::shared_ptr<ICollection>& lv,
								const std::shared_ptr<INTERACTION>& rv,
								std::initializer_list<CollectionObject> object) override;

		Physics() = default;
		~Physics() = default;
};
