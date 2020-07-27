#ifndef SFMLPROJECT_REBUILD_GRID_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_GRID_INTERFACE_HPP

#include <vector>
#include "../object/object.hpp"

namespace PROJECT::GRID
{
	class IGrid
	{
		public:
			virtual void init(float x, float y, float width, float height) noexcept = 0;
			
			virtual size_t sort(const std::vector<std::shared_ptr<OBJECT>>& array) noexcept = 0;

			virtual ~IGrid() = default;
	};
};

#endif // SFMLPROJECT_REBUILD_GRID_INTERFACE_HPP
