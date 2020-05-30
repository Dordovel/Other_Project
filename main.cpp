#include "./headers/core.hpp"
#include "./headers/application.hpp"
#include "./headers/layout.hpp"
#include "./headers/events.hpp"
#include "./headers/database.hpp"
#include "./headers/clock.hpp"
#include "./graphicobject/sprite.hpp"
#include "./headers/physics.hpp"
#include "./headers/view.hpp"
#include "./graphicobject/circle.hpp"
#include "./algorithm/move.hpp"
#include "./headers/layout_dispatcher.hpp"
#include "./graphicobject/text.hpp"
#include "./struct/side.hpp"
#include "./menu_builder.hpp"
#include "./id.hpp"
#include "./headers/npc.hpp"
#include "./headers/animation.hpp"

std::array<std::pair<std::string, std::string>, 4>
 open_select_menu(const std::string& lastItem) noexcept
{
	std::array<std::pair<std::string, std::string>, 4> generateItem;
	
	if(lastItem == NPC_JEREMY_TYPE_ITEM)
	{
		generateItem[0] = std::pair(NPC_JEREMY_PINK, "Pink");
		generateItem[1] = std::pair(NPC_JEREMY_GREEN, "Green");
		generateItem[2] = std::pair(NPC_JEREMY_BLONDE, "Blonde");
	}
	else if(lastItem == NPC_MARTHA_TYPE_ITEM)
	{
		generateItem[0] = std::pair(NPC_MARTHA_PINK, "Pink");
		generateItem[1] = std::pair(NPC_MARTHA_GREEN, "Green");
		generateItem[2] = std::pair(NPC_MARTHA_BLONDE, "Blonde");
	}

	generateItem[3] = std::pair(MENU_BACK_ITEM, "Back");

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 3>
open_type_menu() noexcept
{
	std::array<std::pair<std::string, std::string>, 3> generateItem;

	generateItem[0] = std::pair(NPC_JEREMY_TYPE_ITEM, "Jeremy");
	generateItem[1] = std::pair(NPC_MARTHA_TYPE_ITEM, "Martha");
	generateItem[2] = std::pair(MENU_BACK_ITEM, "Back");

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 2>
open_main_menu() noexcept
{
	std::array<std::pair<std::string, std::string>, 2> generateItem;

	generateItem[0] = std::pair(MAIN_MENU_START_ITEM, "New");
	generateItem[1] = std::pair(MENU_EXIT_ITEM, "Exit");

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 2>
open_pause_menu() noexcept
{
	std::array<std::pair<std::string, std::string>, 2> generateItem;

	generateItem[0] = std::pair(PAUSE_MENU_RESUME_ITEM, "Resume");
	generateItem[1] = std::pair(MENU_EXIT_ITEM, "Main Menu");

	return generateItem;
}

std::shared_ptr<Npc> change_person_type(const std::string& type, const std::shared_ptr<IDataBase>& dataBase) noexcept

{
	const std::string file = "hero/Jeremy/Jeremy_Blonde.png";
	std::shared_ptr<Npc> result = nullptr;

	if(type == NPC_JEREMY_PINK)
	{
		result = std::make_shared<Npc>(dataBase->get_resources(PersonProfession::JEREMY_PINK, SIDE::DOWN));
	}

	else if(type == NPC_MARTHA_PINK)
	{
		result = std::make_shared<Npc>(dataBase->get_resources(PersonProfession::MARTHA_PINK, SIDE::DOWN));
	}

	else if(type == NPC_JEREMY_GREEN)
	{
		result = std::make_shared<Npc>(dataBase->get_resources(PersonProfession::JEREMY_GREEN, SIDE::DOWN));
	}

	else if(type == NPC_MARTHA_GREEN)
	{
		result = std::make_shared<Npc>(dataBase->get_resources(PersonProfession::MARTHA_GREEN, SIDE::DOWN));
	}

	else if(type == NPC_JEREMY_BLONDE)
	{
		result = std::make_shared<Npc>(dataBase->get_resources(PersonProfession::JEREMY_BLONDE, SIDE::DOWN));
	}

	else if(type == NPC_MARTHA_BLONDE)
	{
		result = std::make_shared<Npc>(dataBase->get_resources(PersonProfession::MARTHA_BLONDE, SIDE::DOWN));
	}

	return result;
}	

enum class MenuType
{
	MAIN,
	PAUSE
};


std::string menu(MenuType type, const std::shared_ptr<IApplication>& app, const std::shared_ptr<IView>& view) noexcept
{	
	std::shared_ptr<Core> core	= std::make_shared<Core>();
	core->register_app(app);

	std::shared_ptr<Circle> menuSelectedPointer = std::make_shared<Circle>(8);
	menuSelectedPointer->set_id(MENU_SELECTED_POINTER);
	menuSelectedPointer->visible(true);
	menuSelectedPointer->set_points_count(4);
	
	std::pair menu_bg = MAP_PATH.at("menu");
	std::shared_ptr<Layout> layout = std::make_shared<Layout>(menu_bg.first, menu_bg.second);

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
    std::shared_ptr<View> view = std::make_shared<View>();

    std::shared_ptr<Application> window = std::make_shared<Application>("Test_Game", 700, 500);
    window->init();
    window->set_position(500, 500);
	window->set_view(view);	

    std::shared_ptr<Core> core = std::make_shared<Core>();
	core->register_app(window);

    std::shared_ptr<LayoutDispatcher> layoutDispatcher = std::make_shared<LayoutDispatcher>();

    std::shared_ptr<DataBase> dataBase = std::make_shared<DataBase>(RESOURCES_PATH);

	std::shared_ptr<Clock> clock = std::make_shared<Clock>();

	std::shared_ptr<Anim> anim = std::make_shared<Anim>(0.2f);
	anim->loop(true);
	
	bool isRun = true; 

	while(isRun)
	{
		std::string result = menu(MenuType::MAIN, window, view);
		if(result == MENU_EXIT_ITEM || result == EXIT)
		{
			core->close();
			break;
		}

		std::shared_ptr<Npc> person = nullptr;
		person = change_person_type(result, dataBase);
		person->set_position(1300, 1300);
		person->set_scale(OBJECT_SCALE);
		person->set_id(MAIN_PERSON);

		Animation animationRight;
		animationRight.set_object(person);
		auto arrRight = dataBase->get_animation(SIDE::RIGHT);
		for(const auto& var : arrRight)
			animationRight.add_frame(var);

		Animation animationLeft;
		animationLeft.set_object(person);
		auto arrLeft = dataBase->get_animation(SIDE::LEFT);
		for(const auto& var : arrLeft)
			animationLeft.add_frame(var);
		
		Animation animationUp;
		animationUp.set_object(person);
		auto arrUp = dataBase->get_animation(SIDE::UP);
		for(const auto& var : arrUp)
			animationUp.add_frame(var);

		Animation animationDown;
		animationDown.set_object(person);
		auto arrDown = dataBase->get_animation(SIDE::DOWN);
		for(const auto& var : arrDown)
			animationDown.add_frame(var);

		view->set_position(person->get_position());
		view->set_size(DEFAULT_VIEW_SIZE);
		view->zoom(DEFAULT_VIEW_ZOOM);

		std::pair desert = MAP_PATH.at("forest");
		std::shared_ptr<Layout> mapTower = std::make_shared<Layout>(desert.first, desert.second);
		mapTower->set_id(TOWER_MAP);

		std::shared_ptr<Circle> right = std::make_shared<Circle>(4);
		std::shared_ptr<Circle> left = std::make_shared<Circle>(4);
		std::shared_ptr<Circle> up = std::make_shared<Circle>(4);
		std::shared_ptr<Circle> down = std::make_shared<Circle>(4);

		std::shared_ptr<Move> mover = std::make_shared<Move>();

		std::shared_ptr<IPhysics> physics = std::make_shared<Physics>();

		std::shared_ptr<Events> events= std::make_shared<Events>();
		
		SIDE side = SIDE::STOP;

		events->set_close_window_event([&core, &isRun]()
				{
					core->interrupt(); 
					core->close(); 
					isRun = false;
				});

		events->add_user_event([&anim,
								&clock]()
				{
					anim->run(clock->get_work_time() * DELAY);
				});

		events->add_user_event([&side,
								&anim,
								&animationUp,
								&animationDown,
								&animationLeft,
								&animationRight]()
				{
					if(side != SIDE::STOP)
					{
						if(side == SIDE::LEFT)
						{
							anim->set_animation(&animationLeft);
						}
						if(side == SIDE::RIGHT)
						{
							anim->set_animation(&animationRight);
						}
						
						if(side == SIDE::DOWN)
						{
							anim->set_animation(&animationDown);
						}
						
						if(side == SIDE::UP)
						{
							anim->set_animation(&animationUp);
						}
						anim->stop(false);
					}
					else
					{
						anim->stop(true);
					}
					
				});

		events->add_user_event([&mover,
								&person,
								&side,
								&view,
								&clock]()
				{
					if(side != SIDE::STOP)
					{
						auto val = clock->get_elapsed_time();
						mover->move(side, person, val / DELAY, SPEED);
						mover->move(side, view, val / DELAY, SPEED);
					}
				});

		events->add_user_event([&physics, 
								&layoutDispatcher, 
								&view,
								&right,
								&left,
								&up,
								&down]()
				{
					auto current_layout = layoutDispatcher->get_layout();
					for(auto&& [id, object] : current_layout.second)
					{
						if(physics->check_collision(current_layout.first, object) != CollectionObject::NONE)
						{
							RectangleF rect = object->get_global_bounds();

							right->set_position((rect.left + rect.width), (rect.top + (rect.height / 2)));
							left->set_position(rect.left, (rect.top + (rect.height / 2)));
							up->set_position((rect.left + (rect.width / 2)), rect.top);
							down->set_position((rect.left + (rect.width / 2)), (rect.top + rect.height));


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
									view->block_side(SIDE::UP, true);	
								}
							}

							if(physics->check_collision(current_layout.first, down) != CollectionObject::NONE)
							{
								object->block_side(SIDE::DOWN, true);	

								if(id == MAIN_PERSON)
								{
									view->block_side(SIDE::DOWN, true);	
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

		events->key_pressed_event(Keyboard_Key::Escape, [&window,
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


		events->key_pressed_event(Keyboard_Key::D, [&side]()
				{
					side = SIDE::RIGHT;
				}, EventHandlerType::NONE);

		events->key_pressed_event(Keyboard_Key::A, [&side]()
				{
					side = SIDE::LEFT;
				}, EventHandlerType::NONE);


		events->key_pressed_event(Keyboard_Key::S, [&side]()
				{
					side = SIDE::DOWN;
				}, EventHandlerType::NONE);


		events->key_pressed_event(Keyboard_Key::W, [&side]()
				{
					side = SIDE::UP;
				}, EventHandlerType::NONE);


		events->key_pressed_event(Keyboard_Key::Right, [&side]() 
				{
					side = SIDE::RIGHT;
				}, EventHandlerType::NONE);


		events->key_pressed_event(Keyboard_Key::Left, [&side]()
				{
					side = SIDE::LEFT;
				}, EventHandlerType::NONE);


		events->key_pressed_event(Keyboard_Key::Down, [&side]()
				{
					side = SIDE::DOWN;
				}, EventHandlerType::NONE);


		events->key_pressed_event(Keyboard_Key::Up, [&side]()
				{
					side = SIDE::UP;
				}, EventHandlerType::NONE);

		events->key_released_event(Keyboard_Key::D, [&side]()
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::A, [&side]()
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::S, [&side]()
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::W, [&side]()
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::Right, [&side]() 
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::Left, [&side]()
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::Down, [&side]()
				{
					side = SIDE::STOP;
				});

		events->key_released_event(Keyboard_Key::Up, [&side]()
				{
					side = SIDE::STOP;
				});

		events->add_user_event([&clock]()
				{
					clock->restart();
				});

		core->set_event_dispatcher(events);
		layoutDispatcher->set_layout(mapTower);
		layoutDispatcher->insert_layout_child(person);

		core->set_layout_dispatcher(layoutDispatcher);

		core->run();
	}

	return 0;
}
