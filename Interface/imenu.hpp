#ifndef SFMLPROJECT_REBUILD_MENU_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_MENU_INTERFACE_HPP

#include <memory>
#include "../object/object.hpp"

namespace PROJECT::MENU
{
	class IMenu
	{
		public:
			virtual bool menu_configure(float X, float Y, float Width, float Height) noexcept = 0;

			virtual void add_item(std::shared_ptr<OBJECT> object) noexcept = 0;

			virtual void step_forward() noexcept = 0;

			virtual void step_back() noexcept = 0;

			virtual std::string selected_item() noexcept = 0;

			virtual void reset() noexcept = 0;

			virtual ~IMenu() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_MENU_INTERFACE_HPP
