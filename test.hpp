#ifndef SFMLPROJECT_REBUILD_INVENTORY_HPP
#define SFMLPROJECT_REBUILD_INVENTORY_HPP

#include "./object/object.hpp"
#include "./graphicobject/irectangle.hpp"

class Inventory final
{
	public:
		void add_item(const std::shared_ptr<OBJECT>& item) const;
		void add_items (const std::vector<std::shared_ptr<OBJECT>>& items);

		void menu_configure();
		void selected_item();
};

#endif //SFMLPROJECT_REBUILD_INVENTORY_HPP
