#ifndef SFMLPROJECT_REBUILD_GRID_HPP
#define SFMLPROJECT_REBUILD_GRID_HPP

#include "../Interface/igrid.hpp"

namespace PROJECT::GRID
{
	class Grid : public PROJECT::GRID::IGrid
	{
		private:
			float _x;
			float _y;
			float _height;
			float _width;

		public:
			void init(float x, float y, float width, float height) noexcept override;
			
			size_t sort(const std::vector<std::shared_ptr<OBJECT>>& array) noexcept override;
	};
};

#endif // SFMLPROJECT_REBUILD_GRID_HPP
