#ifndef SFMLPROJECT_REBUILD_MENU_HPP
#define SFMLPROJECT_REBUILD_MENU_HPP

#include "../Interface/imenu.hpp"
#include <vector>
#include "../struct/rect_object.hpp"
#include "../struct/vector_object.hpp"

namespace PROJECT::MENU
{
	class Menu final : public PROJECT::MENU::IMenu
	{
		private:
			std::vector<PROJECT::BASE::DATA::RectangleF> _item;
			PROJECT::BASE::DATA::RectangleF _pointerLeft;
			PROJECT::BASE::DATA::RectangleF _pointerRight;
			float _heightStep;
			float _widthStep;
			std::size_t _index;

		public:
			explicit Menu(float heightStep, float widthStep = 0);

			bool menu_configure() noexcept override;

			void add_item(PROJECT::BASE::DATA::RectangleF bounds) noexcept override;

			void step_forward() noexcept override;

			void step_back() noexcept override;

			int selected_item() noexcept override;

			std::array<PROJECT::BASE::DATA::Vector2F, 2> get_pointer_position() noexcept;

			void reset() noexcept override;

			~Menu() = default;
	};
};

#endif //SFMLPROJECT_REBUILD_MENU_HPP
