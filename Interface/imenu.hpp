#ifndef SFMLPROJECT_REBUILD_MENU_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_MENU_INTERFACE_HPP

#include <memory>

namespace PROJECT
{
	namespace BASE::DATA
	{
		class RectangleF;
	};

	namespace MENU
	{
		class IMenu
		{
			public:
				virtual bool menu_configure() noexcept = 0;

				virtual void add_item(PROJECT::BASE::DATA::RectangleF bounds) noexcept = 0;

				virtual void step_forward() noexcept = 0;

				virtual void step_back() noexcept = 0;

				virtual int selected_item() noexcept = 0;

				virtual void reset() noexcept = 0;

				virtual ~IMenu() = default;
		};
	};
};
#endif //SFMLPROJECT_REBUILD_MENU_INTERFACE_HPP
