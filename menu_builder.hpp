#pragma once

#include "./headers/core.hpp"
#include "./headers/events.hpp"
#include "./item_builder.hpp"
#include "./headers/menu.hpp"
#include "./global.hpp"
#include "./id.hpp"
#include "./headers/layout_dispatcher.hpp"
#include <array>

template <size_t N>
std::string menu_builder(const std::shared_ptr<ICore>& core, 
						const std::shared_ptr<OBJECT>& menuSelectedPointer,
						const std::shared_ptr<ILayout>& layout,
						std::array<std::pair<std::string, std::string>, N>&& generateItem) noexcept
{
	std::shared_ptr<IMenu> menu = std::make_shared<Menu>();
	std::string selectedItem;

	std::shared_ptr<ILayoutDispatcher> dispatcher = std::make_shared<LayoutDispatcher>();
	dispatcher->set_layout(layout);
	dispatcher->insert_layout_child(menuSelectedPointer);

	std::array menuItems = build_items(std::forward<decltype(generateItem)>(generateItem),
																		RESOURCES_PATH + "Font.otf");

	menu->set_pointer(menuSelectedPointer);
	menu->set_layout(layout);

	for(const auto& item : menuItems)
	{
		dispatcher->insert_layout_child(item);
		menu->add_item(item);
	}

	menu->menu_configure();


    std::shared_ptr<IEvents> layoutEvents = std::make_shared<Events>();
	layoutEvents->set_id(EVENT_MENU);

	layoutEvents->set_close_window_event([&selectedItem, &core]()
			{
				selectedItem = EXIT;
				core->interrupt();
			});

	layoutEvents->add_user_event([&menu, &menuItems]()
			{
				std::string item_id = menu->selected_item();

				for(const auto& item : menuItems)
				{
					if(item->get_id() == item_id)
					{
						item->set_color(Color{0, 0, 150});
					}
					else
					{
						item->set_color(Color{0, 0, 0});
					}
				}
			});


	layoutEvents->key_pressed_event(Keyboard_Key::Up, [&menu]()
			{
				menu->step_back();
			}, EventHandlerType::EVENT_LOOP);


	layoutEvents->key_pressed_event(Keyboard_Key::Down, [&menu]()
			{
				menu->step_forward();
			}, EventHandlerType::EVENT_LOOP);


	layoutEvents->key_pressed_event(Keyboard_Key::Enter, [&menu,
														&core,
														&selectedItem]()
			{
				selectedItem = menu->selected_item();
				core->interrupt();
			}, EventHandlerType::EVENT_LOOP);


	core->set_event_dispatcher(layoutEvents);
	core->set_layout_dispatcher(dispatcher);
	
	core->run();

	return selectedItem;
}
