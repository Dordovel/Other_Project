#ifndef SFMLPROJECT_REBUILD_VERTIACAL_GRID__HPP
#define SFMLPROJECT_REBUILD_VERTIACAL_GRID__HPP

#include "../Interface/igrid.hpp"

namespace PROJECT::GRID::VERTICAL
{
	enum class GridAlign
	{
		LEFT,
		CENTER,
		RIGHT
	};

	class VerticalGrid : public PROJECT::GRID::IGrid
	{
		private:
			float _item_offset;
			GridAlign _align = GridAlign::CENTER;
			float _x;
			float _y;
			float _height;
			float _width;

		public:

			VerticalGrid (PROJECT::GRID::VERTICAL::GridAlign align, int offsetY = 0);

			void init(float x, float y, float width, float height) noexcept;

			size_t sort(const std::vector<std::shared_ptr<OBJECT>>& array) noexcept;

			~VerticalGrid() = default;
	};
};


#endif // SFMLPROJECT_REBUILD_VERTIACAL_GRID__HPP
