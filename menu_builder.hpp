#pragma once

#include "headers/keyboard_unit.hpp"
#include "./item_builder.hpp"
#include "./headers/menu.hpp"
#include "./global.hpp"
#include "./id.hpp"
#include <array>
#include "./Interface/iapplication.hpp"
#include "./graphicobject/rectangle.hpp"
#include "./struct/rect_object.hpp"

template <size_t N>
std::string menu_builder(const std::shared_ptr<PROJECT::APPLICATION::IApplication>& app, 
						const std::shared_ptr<OBJECT>& menuSelectedPointer,
						const std::shared_ptr<OBJECT>& layout,
						std::array<std::pair<std::string, std::string>, N>&& generateItem) noexcept
{
	PROJECT::MENU::Menu menu;
	std::string selectedItem;
	menu.set_position(PROJECT::MENU::MenuPosition::LEFT);

	std::array menuItems = build_items(std::forward<decltype(generateItem)>(generateItem),
																		RESOURCES_PATH + "Font.otf");


	for(const auto& item : menuItems)
	{
		menu.add_item(item);
	}

	auto layoutRect = layout->get_global_bounds();

	menu.menu_configure(layoutRect.left, layoutRect.top, layoutRect.width, layoutRect.height);

	menuSelectedPointer->set_position(menu.get_pointer_position());

	bool isRun = true;

    PROJECT::UNIT::CONTROL::KEYBOARD::KeyboardUnit keyboard;

	std::string item_id;

	keyboard.set_close_window_event([&selectedItem, &isRun]()
			{
				selectedItem = EXIT;
				isRun = false;
			});

	keyboard.button_pressed(PROJECT::UNIT::CONTROL::KEYBOARD::Keyboard_Key::Up, [&menu, &menuSelectedPointer]()
			{
				menu.step_back();
				menuSelectedPointer->set_position(menu.get_pointer_position());
			}, PROJECT::UNIT::CONTROL::EventHandlerType::EVENT_LOOP);


	keyboard.button_pressed(PROJECT::UNIT::CONTROL::KEYBOARD::Keyboard_Key::Down, [&menu, &menuSelectedPointer]()
			{
				menu.step_forward();
				menuSelectedPointer->set_position(menu.get_pointer_position());
			}, PROJECT::UNIT::CONTROL::EventHandlerType::EVENT_LOOP);


	keyboard.button_pressed(PROJECT::UNIT::CONTROL::KEYBOARD::Keyboard_Key::Enter, [&menu,
														&isRun,
														&selectedItem]()
			{
				selectedItem = menu.selected_item();
				isRun = false;
			}, PROJECT::UNIT::CONTROL::EventHandlerType::EVENT_LOOP);

	while (app->is_open() && isRun)
	{
		while (app->check_events())
        {
			keyboard.catch_events(app->event_handler());
		}
		
		keyboard.catch_events();

		for(const auto& item : menuItems)
		{
			item_id = menu.selected_item();

			if(item->get_id() == item_id)
			{
				item->set_color(PROJECT::BASE::GRAPHIC::Color::Red);
			}
			else
			{
				item->set_color(PROJECT::BASE::GRAPHIC::Color::Yellow);
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
