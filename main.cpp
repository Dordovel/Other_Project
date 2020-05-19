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
#include "./headers/event_dispatcher.hpp"
#include "./headers/layout_dispatcher.hpp"
#include "./graphicobject/text.hpp"
#include "./struct/side.hpp"
#include "./id.hpp"
#include "./headers/menu.hpp"
#include <unordered_map>

constexpr int SPEED = 2;
const static Vector2F DEFAULT_VIEW_SIZE = {300, 300};
constexpr int DEFAULT_VIEW_ZOOM = 2;
const static std::string NPC_FILE_NAME = "hero.png";
const static Vector2F OBJECT_SCALE = {0.2f, 0.3f};
const static Vector2F CIRCLE_SCALE = {0.2f, 0.2f};
const static std::string RESOURCES_PATH = "./Game_Resources/Image/";
const static std::unordered_map<std::string, std::pair<std::string, std::string>> MAP_PATH = 
									{
										{"menu", std::pair("./Game_Resources/Image/", "main_menu.tmx")},
										{"forest", std::pair("./Game_Resources/Image/forest/", "main.tmx")},
										{"desert", std::pair("./Game_Resources/Image/desert/", "tower.tmx")}
									};
int main()
{
    std::unique_ptr<ICore> core (new Core);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher (new LayoutDispatcher);

	std::shared_ptr<IEventDispatcher> eventsDispatcher (new EventDispatcher);

    std::unique_ptr<IDataBase> dataBase (new DataBase(RESOURCES_PATH));

    std::shared_ptr<IView> view (new View(DEFAULT_VIEW_SIZE));
    view->zoom(DEFAULT_VIEW_ZOOM);

    std::shared_ptr<IApplication> window (new Application("Test_Game", 700, 500));
    window->init();
    window->set_position(500, 500);
    window->set_view(view);	

	std::pair menu = MAP_PATH.at("menu");

//DEFAULT BUTTON
	
	std::shared_ptr<Circle> menuSelectedPointer (new Circle(30));
	menuSelectedPointer->set_id(MENU_SELECTED_POINTER);
	menuSelectedPointer->set_scale(CIRCLE_SCALE);
	menuSelectedPointer->visible(true);

	std::shared_ptr<Text> menuButtonExit (new Text(RESOURCES_PATH + "Font.otf"));
	menuButtonExit->set_text("Exit");
	menuButtonExit->set_color(Color(0, 0, 0));
	menuButtonExit->set_id(MENU_EXIT_ITEM);

//END DEFAULT BUTTON

//MENU PREFER

	Menu npcSelectedMenuPrefer;
	Menu mainMenuPrefer;
	Menu pauseMenuPrefer;

//MAIN MENU
	
	std::shared_ptr<ILayout> mainMenu(new Layout(menu.first, menu.second));
	mainMenu->set_id(MAIN_MENU);
	
	std::shared_ptr<Text> mainMenuButtonStart(new Text(RESOURCES_PATH + "Font.otf"));
	mainMenuButtonStart->set_text("New");
	mainMenuButtonStart->set_color(Color(0, 0, 0));
	mainMenuButtonStart->set_id(MAIN_MENU_START_ITEM);

	mainMenuPrefer.set_pointer(menuSelectedPointer);
	mainMenuPrefer.set_layout(mainMenu);
	mainMenuPrefer.add_item(mainMenuButtonStart);
	mainMenuPrefer.add_item(menuButtonExit);
	mainMenuPrefer.menu_configure();

	Vector2UI mainMenuSize = mainMenu->get_size();
	view->set_position((mainMenuSize.x / 2), (mainMenuSize.y / 2));
	view->set_size(mainMenuSize.x, mainMenuSize.y);

    std::shared_ptr<IEvents> mainMenuEvents (new Events);
	mainMenuEvents->set_id(EVENT_MAIN_MENU);

	std::unordered_map<std::string, std::shared_ptr<Text>> mainMenuItems{	
																			std::pair(menuButtonExit->get_id(), menuButtonExit),
																			std::pair(mainMenuButtonStart->get_id(), mainMenuButtonStart)
																		};
	
	mainMenuEvents->add_user_event([&mainMenuPrefer, &mainMenuItems]()
			{
				std::string item_id = mainMenuPrefer.selected_item();

				for(const auto& item : mainMenuItems)
				{
					if(item.first == item_id)
					{
						item.second->set_color(Color{255, 0, 0});
					}
					else
					{
						item.second->set_color(Color{0, 0, 0});
					}
				}
			});


	mainMenuEvents->add_key_event(Keyboard_Key::Up, [&mainMenuPrefer]()
			{
				mainMenuPrefer.step_back();
			}, EventHandlerType::EVENT_LOOP);


	mainMenuEvents->add_key_event(Keyboard_Key::Down, [&mainMenuPrefer]()
			{
				mainMenuPrefer.step_forward();
			}, EventHandlerType::EVENT_LOOP);


	mainMenuEvents->add_key_event(Keyboard_Key::Enter, [&mainMenuPrefer,
														&core,
														&layoutDispatcher,
														&npcSelectedMenuPrefer,
														&eventsDispatcher]()
			{
				std::string selectedItem = mainMenuPrefer.selected_item();
				if(selectedItem == MENU_EXIT_ITEM)
				{
					core->close();
				}
				else if(selectedItem == MAIN_MENU_START_ITEM)
				{
					//core->shutdown();
					layoutDispatcher->change_layout(NPC_SELECTED_MENU);
					eventsDispatcher->change_event_handler(EVENT_NPC_SELECTED_MENU);
					npcSelectedMenuPrefer.menu_configure();
				}

			}, EventHandlerType::EVENT_LOOP);


//END MAIN MENU


//SELECT NPC TYPE MENU


	std::shared_ptr<ILayout> npcSelectedMenu(new Layout(menu.first, menu.second));
	npcSelectedMenu->set_id(NPC_SELECTED_MENU);
	
	std::shared_ptr<Text> npcSelectedMenuButtonRedType(new Text(RESOURCES_PATH + "Font.otf"));
	npcSelectedMenuButtonRedType->set_text("Red");
	npcSelectedMenuButtonRedType->set_color(Color(0, 0, 0));
	npcSelectedMenuButtonRedType->set_id(NPC_RED_TYPE_ITEM);

	std::shared_ptr<Text> npcSelectedMenuButtonBlueType(new Text(RESOURCES_PATH + "Font.otf"));
	npcSelectedMenuButtonBlueType->set_text("Blue");
	npcSelectedMenuButtonBlueType->set_color(Color(0, 0, 0));
	npcSelectedMenuButtonBlueType->set_id(NPC_BLUE_TYPE_ITEM);

	npcSelectedMenuPrefer.set_pointer(menuSelectedPointer);
	npcSelectedMenuPrefer.set_layout(npcSelectedMenu);
	npcSelectedMenuPrefer.add_item(npcSelectedMenuButtonBlueType);
	npcSelectedMenuPrefer.add_item(npcSelectedMenuButtonRedType);
	npcSelectedMenuPrefer.add_item(menuButtonExit);

	Vector2UI npcSelectedMenuSize = npcSelectedMenu->get_size();
	view->set_position((npcSelectedMenuSize.x / 2), (npcSelectedMenuSize.y / 2));
	view->set_size(npcSelectedMenuSize.x, npcSelectedMenuSize.y);

    std::shared_ptr<IEvents> npcSelectedMenuEvents (new Events);
	npcSelectedMenuEvents->set_id(EVENT_NPC_SELECTED_MENU);

	std::unordered_map<std::string, std::shared_ptr<Text>> npcSelectedMenuItems{
																				std::pair(menuButtonExit->get_id(), menuButtonExit),
																				std::pair( npcSelectedMenuButtonRedType->get_id(), npcSelectedMenuButtonRedType),
																				std::pair(npcSelectedMenuButtonBlueType->get_id(), npcSelectedMenuButtonBlueType)
																			};
	
	npcSelectedMenuEvents->add_user_event([&npcSelectedMenuPrefer, &npcSelectedMenuItems]()
			{
				std::string item_id = npcSelectedMenuPrefer.selected_item();

				for(const auto& item : npcSelectedMenuItems)
				{
					if(item.first == item_id)
					{
						item.second->set_color(Color{255, 0, 0});
					}
					else
					{
						item.second->set_color(Color{0, 0, 0});
					}
				}
			});


	npcSelectedMenuEvents->add_key_event(Keyboard_Key::Up, [&npcSelectedMenuPrefer]()
			{
				npcSelectedMenuPrefer.step_back();
			}, EventHandlerType::EVENT_LOOP);


	npcSelectedMenuEvents->add_key_event(Keyboard_Key::Down, [&npcSelectedMenuPrefer]()
			{
				npcSelectedMenuPrefer.step_forward();
			}, EventHandlerType::EVENT_LOOP);


	npcSelectedMenuEvents->add_key_event(Keyboard_Key::Enter, [&mainMenuPrefer,
														&layoutDispatcher,
														&npcSelectedMenuPrefer,
														&eventsDispatcher]()
			{
				std::string selectedItem = npcSelectedMenuPrefer.selected_item();
				if(selectedItem == MENU_EXIT_ITEM)
				{
					layoutDispatcher->change_layout(MAIN_MENU);
					eventsDispatcher->change_event_handler(EVENT_MAIN_MENU);
					mainMenuPrefer.menu_configure();
				}

			}, EventHandlerType::EVENT_LOOP);


//END SELECT NPC TYPE MENU

	layoutDispatcher->add_layout(npcSelectedMenu->get_id(), npcSelectedMenu);
	layoutDispatcher->insert_layout_child(npcSelectedMenu->get_id(), menuSelectedPointer->get_id(), menuSelectedPointer);
	layoutDispatcher->insert_layout_child(npcSelectedMenu->get_id(), npcSelectedMenuButtonBlueType->get_id(), npcSelectedMenuButtonBlueType);
	layoutDispatcher->insert_layout_child(npcSelectedMenu->get_id(), npcSelectedMenuButtonRedType->get_id(), npcSelectedMenuButtonRedType);
	layoutDispatcher->insert_layout_child(npcSelectedMenu->get_id(), menuButtonExit->get_id(), menuButtonExit);

	layoutDispatcher->add_layout(mainMenu->get_id(), mainMenu);
	layoutDispatcher->insert_layout_child(mainMenu->get_id(), menuSelectedPointer->get_id(), menuSelectedPointer);
	layoutDispatcher->insert_layout_child(mainMenu->get_id(), mainMenuButtonStart->get_id(), mainMenuButtonStart);
	layoutDispatcher->insert_layout_child(mainMenu->get_id(), menuButtonExit->get_id(), menuButtonExit);

	eventsDispatcher->register_event_handler(mainMenuEvents->get_id(), mainMenuEvents);
	eventsDispatcher->register_event_handler(npcSelectedMenuEvents->get_id(), npcSelectedMenuEvents);

	eventsDispatcher->change_event_handler(mainMenuEvents->get_id());
	layoutDispatcher->change_layout(mainMenu->get_id());

    core->register_app(std::move(window));
	core->set_layout_dispatcher(layoutDispatcher);
    core->set_event_dispatcher(eventsDispatcher);

	core->run();




	if(core->is_run())
	{
		layoutDispatcher->remove_layout(MAIN_MENU);
		layoutDispatcher->remove_layout(NPC_SELECTED_MENU);

		layoutDispatcher->change_layout(TOWER_MAP);
		eventsDispatcher->change_event_handler(EVENT_MAP);

		std::shared_ptr<Image> person (new Image(dataBase->get_resources(PersonProfession::Magic, NPC_FILE_NAME)));
		person->set_id(MAIN_PERSON);
		person->set_position(1300, 1300);
		person->set_scale(OBJECT_SCALE);

		view->set_size(DEFAULT_VIEW_SIZE);
		view->zoom(DEFAULT_VIEW_ZOOM);
		view->set_position(person->get_position());

		std::shared_ptr<Circle> circle (new Circle(40));
		circle->set_id(MOUSE_POINTER);
		circle->set_scale(CIRCLE_SCALE);

		
		std::pair desert = MAP_PATH.at("desert");
		std::shared_ptr<ILayout> mapTower (new Layout(desert.first, desert.second));
		mapTower->set_id(TOWER_MAP);
		
		std::pair forest = MAP_PATH.at("forest");
		std::shared_ptr<ILayout> mapForest (new Layout(forest.first, forest.second));
		mapForest->set_id(FOREST_MAP);

		std::shared_ptr<IEvents> mainEvents (new Events);
		mainEvents->set_id(EVENT_MAP);


		std::shared_ptr<ILayout> pauseMenu (new Layout(menu.first, menu.second));
		pauseMenu->set_id(PAUSE_MENU);

		std::shared_ptr<IEvents> pauseMenuEvents (new Events);
		pauseMenuEvents->set_id(EVENT_PAUSE_MENU);
		
		std::shared_ptr<Text> pauseMenuButtonResume (new Text(RESOURCES_PATH + "Font.otf"));
		pauseMenuButtonResume->set_text("Resume");
		pauseMenuButtonResume->set_color(Color(0, 0, 0));
		pauseMenuButtonResume->set_id(PAUSE_MENU_RESUME_ITEM);

		std::shared_ptr<Text> pauseMenuButtonTest1 (new Text(RESOURCES_PATH + "Font.otf"));
		pauseMenuButtonTest1->set_text("Test1");
		pauseMenuButtonTest1->set_color(Color(0, 0, 0));
		pauseMenuButtonTest1->set_id("TEST1");

		std::shared_ptr<Text> pauseMenuButtonTest2 (new Text(RESOURCES_PATH + "Font.otf"));
		pauseMenuButtonTest2->set_text("Test2");
		pauseMenuButtonTest2->set_color(Color(0, 0, 0));
		pauseMenuButtonTest2->set_id("TEST2");

		std::unordered_map<std::string, std::shared_ptr<Text>> pauseMenuItems{
																	std::pair(menuButtonExit->get_id(), menuButtonExit),
																	std::pair(pauseMenuButtonTest2->get_id(), pauseMenuButtonTest2), 
																	std::pair(pauseMenuButtonTest1->get_id(), pauseMenuButtonTest1), 
																	std::pair(pauseMenuButtonResume->get_id(), pauseMenuButtonResume)
																};
		pauseMenuPrefer.set_pointer(menuSelectedPointer);
		pauseMenuPrefer.set_layout(pauseMenu);

		for(const auto& var : pauseMenuItems)
		{
			pauseMenuPrefer.add_item(var.second);
		}


		std::shared_ptr<Circle> right(new Circle(4));
		std::shared_ptr<Circle> left(new Circle(4));
		std::shared_ptr<Circle> up(new Circle(4));
		std::shared_ptr<Circle> down(new Circle(4));

		std::shared_ptr<IClock> clock (new Clock(8000));
		std::shared_ptr<IMove> mover (new Move);
		std::shared_ptr<IPhysics> physics (new Physics);


		mainEvents->add_user_event([&physics, 
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


		mainEvents->set_close_window_event([&core](){core->close();});

		
		mainEvents->add_user_event([&clock](){clock->restart();});


		mainEvents->mouse_button_pressed(Mouse_Key::Left, [&circle,
														   window,
														   &person,
														   physics,
														   &mover,
														   &layoutDispatcher,
														   &clock](int X, int Y)
				 {
					Vector2F coordinates = window->map_pixel_to_coords(X, Y);
					circle->visible(true);
					circle->set_position(coordinates);
					mover->move(person, clock, physics, layoutDispatcher->get_layout().first, coordinates, SPEED);
				 });


		mainEvents->mouse_button_released([&circle](){circle->visible(false);});


		mainEvents->add_key_event(Keyboard_Key::Escape, [&layoutDispatcher,
														&eventsDispatcher,
														&view,
														&pauseMenuPrefer]()
				{
					layoutDispatcher->change_layout(PAUSE_MENU);
					eventsDispatcher->change_event_handler(EVENT_PAUSE_MENU);
					auto menu = layoutDispatcher->get_layout();
					Vector2UI menuSize = menu.first->get_size();
					view->set_position((menuSize.x / 2), (menuSize.y / 2));
					view->set_size(menuSize.x, menuSize.y);
					pauseMenuPrefer.menu_configure();

				}, EventHandlerType::EVENT_LOOP);


		mainEvents->add_key_event(Keyboard_Key::D, [&mover,
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::RIGHT, person, clock->get_time(), SPEED);
					mover->move(SIDE::RIGHT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);

		mainEvents->add_key_event(Keyboard_Key::A, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::LEFT, person, clock->get_time(), SPEED);
					mover->move(SIDE::LEFT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		mainEvents->add_key_event(Keyboard_Key::S, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::DOWN, person, clock->get_time(), SPEED);
					mover->move(SIDE::DOWN, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		mainEvents->add_key_event(Keyboard_Key::W, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::UP, person, clock->get_time(), SPEED);
					mover->move(SIDE::UP, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		mainEvents->add_key_event(Keyboard_Key::Right, [&mover, 
														&person, 
														&clock, 
														&view]()
				{
					mover->move(SIDE::RIGHT, person, clock->get_time(), SPEED);
					mover->move(SIDE::RIGHT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		mainEvents->add_key_event(Keyboard_Key::Left, [&mover,
														&person,
														&clock, 
														&view]()
				{
					mover->move(SIDE::LEFT, person, clock->get_time(), SPEED);
					mover->move(SIDE::LEFT, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		mainEvents->add_key_event(Keyboard_Key::Down, [&mover,
														&person,
														&clock, 
														&view]()
				{
					mover->move(SIDE::DOWN, person, clock->get_time(), SPEED);
					mover->move(SIDE::DOWN, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		mainEvents->add_key_event(Keyboard_Key::Up, [&mover, 
													&person, 
													&clock, 
													&view]()
				{
					mover->move(SIDE::UP, person, clock->get_time(), SPEED);
					mover->move(SIDE::UP, view, clock->get_time(), SPEED);
				}, EventHandlerType::NONE);


		pauseMenuEvents->add_user_event([&pauseMenuPrefer, &pauseMenuItems]()
				{
					std::string item_id = pauseMenuPrefer.selected_item();

					for(const auto& item : pauseMenuItems)
					{
						if(item.first == item_id)
						{
							item.second->set_color(Color{255, 0, 0});
						}
						else
						{
							item.second->set_color(Color{0, 0, 0});
						}
					}
				});

		pauseMenuEvents->add_key_event(Keyboard_Key::Up, [&pauseMenuPrefer]()
				{
					pauseMenuPrefer.step_back();
				}, EventHandlerType::EVENT_LOOP);

		pauseMenuEvents->add_key_event(Keyboard_Key::Down, [&pauseMenuPrefer]()
				{
					pauseMenuPrefer.step_forward();
				}, EventHandlerType::EVENT_LOOP);


		pauseMenuEvents->add_key_event(Keyboard_Key::Enter, [&pauseMenuPrefer,
														&layoutDispatcher,
														&eventsDispatcher,
														&core,
														&view,
														&person]()
				{
					std::string selectedItem = pauseMenuPrefer.selected_item();
					if(selectedItem == MENU_EXIT_ITEM)
					{
						core->close();
					}
					else if(selectedItem == PAUSE_MENU_RESUME_ITEM)
					{
						layoutDispatcher->change_layout(layoutDispatcher->get_change_history().back());
						eventsDispatcher->change_event_handler(EVENT_MAP);
						view->set_position(person->get_position());
						view->set_size(DEFAULT_VIEW_SIZE);
						view->zoom(DEFAULT_VIEW_ZOOM);
					}

				}, EventHandlerType::EVENT_LOOP);



		layoutDispatcher->add_layout(pauseMenu->get_id(), pauseMenu);
		layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonResume->get_id(), pauseMenuButtonResume);
		layoutDispatcher->insert_layout_child(pauseMenu->get_id(), menuSelectedPointer->get_id(), menuSelectedPointer);
		layoutDispatcher->insert_layout_child(pauseMenu->get_id(), menuButtonExit->get_id(), menuButtonExit);
		layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonTest1->get_id(), pauseMenuButtonTest1);
		layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonTest2->get_id(), pauseMenuButtonTest2);

		layoutDispatcher->add_layout(mapForest->get_id(), mapForest);
		layoutDispatcher->insert_layout_child(mapForest->get_id(), person->get_id(), person);

		layoutDispatcher->add_layout(mapTower->get_id(), mapTower);
		layoutDispatcher->insert_layout_child(mapTower->get_id(), person->get_id(), person);
		layoutDispatcher->add_object(circle->get_id(), circle);


		eventsDispatcher->register_event_handler(mainEvents->get_id(), mainEvents);
		eventsDispatcher->register_event_handler(pauseMenuEvents->get_id(), pauseMenuEvents);

		core->run();
	}

    return EXIT_SUCCESS;
}
