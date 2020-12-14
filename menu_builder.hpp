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
#include "./headers/vertical_grid.hpp"

template <size_t N>
std::string menu_builder(const std::shared_ptr<PROJECT::APPLICATION::IApplication>& app, 
						const std::shared_ptr<OBJECT>& menuSelectedPointer,
						const std::shared_ptr<OBJECT>& layout,
						std::array<std::pair<std::string, std::string>, N>&& generateItem) noexcept
{
	PROJECT::MENU::Menu menu(20.f);
	int selectedItem;

	std::array menuItems = build_items(std::forward<decltype(generateItem)>(generateItem),
																		RESOURCES_PATH + "Font.otf");

	float step = 20;
	auto layoutRect = layout->get_global_bounds();

	PROJECT::GRID::VERTICAL::VerticalGrid grid(PROJECT::GRID::VERTICAL::GridAlign::CENTER, step);
	grid.init(layoutRect.left, layoutRect.top, layoutRect.width, layoutRect.height);
	grid.sort(std::vector<std::shared_ptr<OBJECT>>(std::begin(menuItems), std::end(menuItems)));

	for(const auto& item : menuItems)
		menu.add_item(item->get_global_bounds());

	menu.menu_configure();

	auto pointers = menu.get_pointer_position();

	menuSelectedPointer->set_position(pointers[1]);
	auto leftPointer = menuSelectedPointer->clone();
	leftPointer->set_position(pointers[0]);

	bool isRun = true;

    PROJECT::UNIT::CONTROL::KEYBOARD::KeyboardUnit keyboard;

	keyboard.button_pressed(PROJECT::UNIT::CONTROL::KEYBOARD::Keyboard_Key::Up, [&menu,
																				&menuSelectedPointer,
																				&leftPointer]()
			{
				menu.step_back();

				auto pointers = menu.get_pointer_position();
				menuSelectedPointer->set_position(pointers[1]);
				leftPointer->set_position(pointers[0]);

			}, PROJECT::UNIT::CONTROL::EventHandlerType::EVENT_LOOP);


	keyboard.button_pressed(PROJECT::UNIT::CONTROL::KEYBOARD::Keyboard_Key::Down, [&menu,
																					&menuSelectedPointer,
																					&leftPointer]()
			{
				menu.step_forward();

				auto pointers = menu.get_pointer_position();
				menuSelectedPointer->set_position(pointers[1]);
				leftPointer->set_position(pointers[0]);

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

		menuItems[selectedItem]->set_color(PROJECT::BASE::GRAPHIC::Color::White);
		selectedItem = menu.selected_item();
		menuItems[selectedItem]->set_color(PROJECT::BASE::GRAPHIC::Color::Red);

		app->draw(layout.get());
		app->draw(menuSelectedPointer.get());
		app->draw(leftPointer.get());

		for(const auto& pointers : menuItems)
		{
			app->draw(pointers.get());
		}

		app->display();
	}


	return generateItem[selectedItem].second;
}
