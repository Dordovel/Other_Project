#pragma once

#include "./headers/events.hpp"
#include "./item_builder.hpp"
#include "./headers/menu.hpp"
#include "./global.hpp"
#include "./id.hpp"
#include <array>
#include "./Interface/iapplication.hpp"

template <size_t N>
std::string menu_builder(const std::shared_ptr<PROJECT::APPLICATION::IApplication>& app, 
						std::shared_ptr<OBJECT> menuSelectedPointer,
						std::shared_ptr<PROJECT::COLLECTION::ILayout> layout,
						std::array<std::pair<std::string, std::string>, N>&& generateItem) noexcept
{
	std::shared_ptr<PROJECT::MENU::IMenu> menu = std::make_shared<PROJECT::MENU::Menu>();
	std::string selectedItem;

	std::array menuItems = build_items(std::forward<decltype(generateItem)>(generateItem),
																		RESOURCES_PATH + "Font.otf");

	menu->set_pointer(menuSelectedPointer);
	menu->set_layout(layout);

	for(const auto& item : menuItems)
	{
		menu->add_item(item);
	}

	menu->menu_configure();

	bool isRun = true;

    std::shared_ptr<PROJECT::EVENT::IEvents> events = std::make_shared<PROJECT::EVENT::Events>(EVENT_MENU);

	std::string item_id;

	events->set_close_window_event([&selectedItem, &isRun]()
			{
				selectedItem = EXIT;
				isRun = false;
			});

	events->key_pressed_event(PROJECT::EVENT::Keyboard_Key::Up, [&menu]()
			{
				menu->step_back();
			}, PROJECT::EVENT::EventHandlerType::EVENT_LOOP);


	events->key_pressed_event(PROJECT::EVENT::Keyboard_Key::Down, [&menu]()
			{
				menu->step_forward();
			}, PROJECT::EVENT::EventHandlerType::EVENT_LOOP);


	events->key_pressed_event(PROJECT::EVENT::Keyboard_Key::Enter, [&menu,
														&isRun,
														&selectedItem]()
			{
				selectedItem = menu->selected_item();
				isRun = false;
			}, PROJECT::EVENT::EventHandlerType::EVENT_LOOP);

	while (app->is_open() && isRun)
	{
		while (app->event_handler(events->get_event_object()))
		{
			events->catch_events_loop();
		}
		
		events->catch_events_none();

		for(const auto& item : menuItems)
		{
			item_id = menu->selected_item();

			if(item->get_id() == item_id)
			{
				item->set_color(PROJECT::BASE::GRAPHIC::Color::Red);
			}
			else
			{
				item->set_color(PROJECT::BASE::GRAPHIC::Color::Green);
			}
		}
	
		app->draw(layout);
		app->draw(menuSelectedPointer);

		for(const auto& pointers : menuItems)
		{
			app->draw(pointers);
		}

		app->display();
	}


	return selectedItem;
}
