#include "./headers/core.hpp"
#include "./headers/application.hpp"
#include "./headers/layout.hpp"
#include "./headers/events.hpp"
#include "./headers/database.hpp"
#include "./headers/clock.hpp"
#include "./graphicobject/image.hpp"
#include "./headers/physics.hpp"
#include "./headers/view.hpp"
#include "./graphicobject/circle.hpp"
#include "./algorithm/move.hpp"
#include "./headers/layout_dispatcher.hpp"
#include "./graphicobject/text.hpp"
#include "./struct/side.hpp"
#include "./menu_builder.hpp"
#include "./id.hpp"


std::array<std::pair<std::string, std::string>, 5>
 open_select_menu(const std::string& lastItem)
{
	std::array<std::pair<std::string, std::string>, 5> generateItem;
	
	if(lastItem == NPC_RED_TYPE_ITEM)
	{
		generateItem[0] = std::pair(NPC_RED_PALADIN, "Paladin");
		generateItem[1] = std::pair(NPC_RED_MAGIC, "Magic");
		generateItem[2] = std::pair(NPC_RED_BERSERK, "Berserk");
		generateItem[3] = std::pair(NPC_RED_WARRIOR, "Warrior");
	}
	else if(lastItem == NPC_BLUE_TYPE_ITEM)
	{
		generateItem[0] = std::pair(NPC_BLUE_PALADIN, "Paladin");
		generateItem[1] = std::pair(NPC_BLUE_MAGIC, "Magic");
		generateItem[2] = std::pair(NPC_BLUE_BERSERK, "Berserk");
		generateItem[3] = std::pair(NPC_BLUE_WARRIOR, "Warrior");
	}

	generateItem[4] = std::pair(MENU_BACK_ITEM, "Back");

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 3>
open_type_menu()
{
	std::array<std::pair<std::string, std::string>, 3> generateItem;

	generateItem[0] = std::pair(NPC_BLUE_TYPE_ITEM, "Blue");
	generateItem[1] = std::pair(NPC_RED_TYPE_ITEM, "Red");
	generateItem[2] = std::pair(MENU_BACK_ITEM, "Back");

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 2>
open_main_menu()
{
	std::array<std::pair<std::string, std::string>, 2> generateItem;

	generateItem[0] = std::pair(MAIN_MENU_START_ITEM, "New");
	generateItem[1] = std::pair(MENU_EXIT_ITEM, "Exit");

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 2>
open_pause_menu()
{
	std::array<std::pair<std::string, std::string>, 2> generateItem;

	generateItem[0] = std::pair(PAUSE_MENU_RESUME_ITEM, "Resume");
	generateItem[1] = std::pair(MENU_EXIT_ITEM, "Main Menu");

	return generateItem;
}

std::shared_ptr<Image> change_person_type(const std::string& type, const std::shared_ptr<IDataBase>& dataBase)

{
	const std::string file = "hero.png";
	std::shared_ptr<Image> result = nullptr;

	if(type == NPC_RED_PALADIN)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::PaladinRed, file));
	}

	else if(type == NPC_RED_MAGIC)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::MagicRed, file));
	}

	else if(type == NPC_RED_BERSERK)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::BerserkRed, file));
	}

	else if(type == NPC_RED_WARRIOR)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::WarriorRed, file));
	}

	else if(type == NPC_BLUE_PALADIN)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::Paladin, file));
	}

	else if(type == NPC_BLUE_MAGIC)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::Magic, file));
	}

	else if(type == NPC_BLUE_BERSERK)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::Berserk, file));
	}

	else if(type == NPC_BLUE_WARRIOR)
	{
		result = std::make_shared<Image>(dataBase->get_resources(PersonProfession::Warrior, file));
	}


	return result;
}	

enum class MenuType
{
	MAIN,
	PAUSE
};


std::string menu(MenuType type, const std::shared_ptr<IApplication>& app, const std::shared_ptr<IView>& view)
{	
	std::shared_ptr<ICore> core= std::make_shared<Core>();
	core->register_app(app);

	std::shared_ptr<Circle> menuSelectedPointer = std::make_shared<Circle>(8);
	menuSelectedPointer->set_id(MENU_SELECTED_POINTER);
	menuSelectedPointer->visible(true);
	menuSelectedPointer->set_points_count(4);
	
	std::pair menu_bg = MAP_PATH.at("menu");
	std::shared_ptr<ILayout> layout = std::make_shared<Layout>(menu_bg.first, menu_bg.second);

	Vector2UI layoutSize = layout->get_size();
	view->set_position((layoutSize.x / 2), (layoutSize.y / 2));
	view->set_size(layoutSize.x, layoutSize.y);

	std::string result;

	if(type == MenuType::MAIN)
	{
		bool isMainMenu = true;
		bool isSecondMenu = true;

		while(isMainMenu)
		{
			layout->set_id(MAIN_MENU);
			result = menu_builder(core, menuSelectedPointer,layout, open_main_menu());

			if(result == MAIN_MENU_START_ITEM)
			{
				while(isSecondMenu)
				{
					layout->set_id(NPC_SELECT_TYPE_MENU);
					result = menu_builder(core, menuSelectedPointer,layout, open_type_menu());

					if(result == MENU_BACK_ITEM)
					{
						break;
					}
					else if(result == EXIT)
					{
						isMainMenu = false;
						isSecondMenu = false;
					}
					else
					{
						layout->set_id(NPC_SELECT_MENU);
						result = menu_builder(core, menuSelectedPointer,layout, open_select_menu(result));
						
						if(result == MENU_BACK_ITEM)
						{
							continue;
						}
						else 
						{
							isMainMenu = false;
							isSecondMenu = false;
						}
					}
				}
			}
			else
			{
				isMainMenu = false;
			}
		}
	}
	else
	{
		layout->set_id(PAUSE_MENU);
		result = menu_builder(core, menuSelectedPointer,layout, open_pause_menu());
	}

	return result;
}

int main()
{
    std::shared_ptr<IView> view = std::make_shared<View>();

    std::shared_ptr<IApplication> window = std::make_shared<Application>("Test_Game", 700, 500);
    window->init();
    window->set_position(500, 500);
	window->set_view(view);	

    std::shared_ptr<ICore> core = std::make_shared<Core>();
	core->register_app(window);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher = std::make_shared<LayoutDispatcher>();

    std::shared_ptr<IDataBase> dataBase = std::make_shared<DataBase>(RESOURCES_PATH);


	bool isRun = true; 

	while(isRun)
	{
		std::string result = menu(MenuType::MAIN, window, view);
		if(result == MENU_EXIT_ITEM || result == EXIT)
		{
			core->close();
			break;
		}

		std::shared_ptr<Image> person = nullptr;
		person = change_person_type(result, dataBase);
		person->set_scale(OBJECT_SCALE);
		person->set_position(1300, 1300);
		person->set_id(MAIN_PERSON);
		
		view->set_position(person->get_position());
		view->set_size(DEFAULT_VIEW_SIZE);
		view->zoom(DEFAULT_VIEW_ZOOM);

		std::pair desert = MAP_PATH.at("desert");
		std::shared_ptr<ILayout> mapTower = std::make_shared<Layout>(desert.first, desert.second);
		mapTower->set_id(TOWER_MAP);

		std::shared_ptr<Circle> right = std::make_shared<Circle>(4);
		std::shared_ptr<Circle> left = std::make_shared<Circle>(4);
		std::shared_ptr<Circle> up = std::make_shared<Circle>(4);
		std::shared_ptr<Circle> down = std::make_shared<Circle>(4);

		std::shared_ptr<IClock> clock = std::make_shared<Clock>(8000);
		std::shared_ptr<IMove> mover = std::make_shared<Move>();
		std::shared_ptr<IPhysics> physics = std::make_shared<Physics>();

		std::shared_ptr<IEvents> events= std::make_shared<Events>();

		events->add_user_event([&physics, 
									&layoutDispatcher, 
									&view,
									&right,
									&left,
									&up,
									&down]()
				{
					auto current_layout = layoutDispatcher->get_layout();
					int value = 20;

					for(auto&& [id, object] : current_layout.second)
					{
						if(physics->check_collision(current_layout.first, object) != CollectionObject::NONE)
						{
							Vector2F current_position = object->get_position();

							right->set_position(current_position.x + 30, current_position.y + value);
							left->set_position(current_position.x - value, current_position.y + value);
							up->set_position(current_position.x + 4, current_position.y - value);
							down->set_position(current_position.x + 4, current_position.y + 50);

							if(physics->check_collision(current_layout.first, right) != CollectionObject::NONE)
							{
								object->block_side(SIDE::RIGHT, true);
								
								if(id == MAIN_PERSON)
								{
									view->block_side(SIDE::RIGHT, true);	
								}
							}
							
							if(physics->check_collision(current_layout.first, left) != CollectionObject::NONE)
							{
								object->block_side(SIDE::LEFT, true);	

								if(id == MAIN_PERSON)
								{
									view->block_side(SIDE::LEFT, true);	
								}
							}

							if(physics->check_collision(current_layout.first, up) != CollectionObject::NONE)
							{
								object->block_side(SIDE::UP, true);	

								if(id == MAIN_PERSON)
								{
									view->block_side(SIDE::LEFT, true);	
								}
							}

							if(physics->check_collision(current_layout.first, down) != CollectionObject::NONE)
							{
								object->block_side(SIDE::DOWN, true);	

								if(id == MAIN_PERSON)
								{
									view->block_side(SIDE::LEFT, true);	
								}
							}
						}
						else
						{
							object->block_side(SIDE::LEFT, false);
							object->block_side(SIDE::UP, false);
							object->block_side(SIDE::RIGHT, false);
							object->block_side(SIDE::DOWN, false);

							if(id == MAIN_PERSON)
							{
								view->block_side(SIDE::LEFT, false);
								view->block_side(SIDE::UP, false);
								view->block_side(SIDE::RIGHT, false);
								view->block_side(SIDE::DOWN, false);
							}
						}
					}
				});


		events->set_close_window_event([&core, &isRun]()
				{
					core->interrupt(); 
					core->close(); 
					isRun = false;
				});

		
		events->add_user_event([&clock](){clock->restart();});

		events->add_key_event(Keyboard_Key::Escape, [&window,
														&view,
														&person,
														&core]()
				{
					std::string result = menu(MenuType::PAUSE, window, view);
					if(result == PAUSE_MENU_RESUME_ITEM)
					{
						view->set_position(person->get_position());
						view->set_size(DEFAULT_VIEW_SIZE);
						view->zoom(DEFAULT_VIEW_ZOOM);
					}
					else
					{
						core->interrupt();
					}
				}, EventHandlerType::EVENT_LOOP);


		events->add_key_event(Keyboard_Key::D, [&mover,
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::RIGHT, person, clock->get_time(), SPEED);
					mover->move(SIDE::RIGHT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);

		events->add_key_event(Keyboard_Key::A, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::LEFT, person, clock->get_time(), SPEED);
					mover->move(SIDE::LEFT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		events->add_key_event(Keyboard_Key::S, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::DOWN, person, clock->get_time(), SPEED);
					mover->move(SIDE::DOWN, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		events->add_key_event(Keyboard_Key::W, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::UP, person, clock->get_time(), SPEED);
					mover->move(SIDE::UP, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		events->add_key_event(Keyboard_Key::Right, [&mover, 
														&person, 
														&clock, 
														&view]()
				{
					mover->move(SIDE::RIGHT, person, clock->get_time(), SPEED);
					mover->move(SIDE::RIGHT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		events->add_key_event(Keyboard_Key::Left, [&mover,
														&person,
														&clock, 
														&view]()
				{
					mover->move(SIDE::LEFT, person, clock->get_time(), SPEED);
					mover->move(SIDE::LEFT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		events->add_key_event(Keyboard_Key::Down, [&mover,
														&person,
														&clock, 
														&view]()
				{
					mover->move(SIDE::DOWN, person, clock->get_time(), SPEED);
					mover->move(SIDE::DOWN, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		events->add_key_event(Keyboard_Key::Up, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::UP, person, clock->get_time(), SPEED);
					mover->move(SIDE::UP, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);

		core->set_event_dispatcher(events);
		layoutDispatcher->set_layout(mapTower);
		layoutDispatcher->insert_layout_child(person);

		core->set_layout_dispatcher(layoutDispatcher);

		core->run();
	}

	return 0;
}
