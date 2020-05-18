#include "./struct/rectobject.hpp"
#include "./headers/core.hpp"
#include "./headers/application.hpp"
#include "./headers/layout.hpp"
#include "./headers/events.hpp"
#include "./headers/database.hpp"
#include "./headers/clock.hpp"
#include "./graphicobject/image.hpp"
#include "./headers/physics.hpp"
#include "./headers/compass.hpp"
#include "./headers/view.hpp"
#include "./graphicobject/circle.hpp"
#include "./algorithm/move.hpp"
#include "./headers/event_dispatcher.hpp"
#include "./headers/layout_dispatcher.hpp"
#include "./graphicobject/text.hpp"
#include "./struct/side.hpp"
#include "./id.hpp"
#include "./headers/menu.hpp"

constexpr int SPEED = 2;
const static Vector2F DEFAULT_VIEW_SIZE = {300, 300};
constexpr int DEFAULT_VIEW_ZOOM = 2;
const static std::string NPC_FILE_NAME = "hero.png";
const static Vector2F OBJECT_SCALE = {0.2f, 0.3f};
const static Vector2F CIRCLE_SCALE = {0.2f, 0.2f};
const static std::string RESOURCES_PATH = "./Game_Resources/Image/";
const static std::map<std::string, std::pair<std::string, std::string>> MAP_PATH = 
									{
										{"menu", std::pair("./Game_Resources/Image/", "main_menu.tmx")},
										{"forest", std::pair("./Game_Resources/Image/forest/", "main.tmx")},
										{"desert", std::pair("./Game_Resources/Image/desert/", "tower.tmx")}
									};
int main()
{
	std::shared_ptr<Menu> prefer_menu(new Menu);

    std::unique_ptr<ICore> core (new Core);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher (new LayoutDispatcher);

	std::shared_ptr<IEventDispatcher> eventsDispatcher (new EventDispatcher);

    std::unique_ptr<IDataBase> dataBase (new DataBase(RESOURCES_PATH));

	std::shared_ptr<IPhysics> physics (new Physics);

    std::shared_ptr<IApplication> window (new Application("Test_Game", 700, 500));

    std::shared_ptr<IClock> clock (new Clock(8000));
   
    std::shared_ptr<IMove> mover (new Move);

    std::shared_ptr<IEvents> mainEvents (new Events);
	mainEvents->set_id(EVENT_MAP);

    std::shared_ptr<IEvents> menuEvents (new Events);
	menuEvents->set_id(EVENT_PAUSE_MENU);

	std::pair desert = MAP_PATH.at("desert");
	std::shared_ptr<ILayout> mapTower (new Layout(desert.first, desert.second));
    mapTower->set_id(TOWER_MAP);
    
	std::pair forest = MAP_PATH.at("forest");
	std::shared_ptr<ILayout> mapForest (new Layout(forest.first, forest.second));
	mapForest->set_id(FOREST_MAP);

	std::shared_ptr<Image> person (new Image(dataBase->get_resources(PersonProfession::Magic, NPC_FILE_NAME)));
    person->set_id(MAIN_PERSON);
    person->set_position(1300, 1300);
	person->set_scale(OBJECT_SCALE);

    std::shared_ptr<IView> view (new View(person->get_position(), DEFAULT_VIEW_SIZE));
    view->zoom(DEFAULT_VIEW_ZOOM);

    std::shared_ptr<Circle> circle (new Circle(40));
    circle->set_id(MOUSE_POINTER);
	circle->set_scale(CIRCLE_SCALE);
 	

	std::pair menu = MAP_PATH.at("menu");
	std::shared_ptr<ILayout> pauseMenu (new Layout(menu.first, menu.second));
    pauseMenu->set_id(PAUSE_MENU);

	std::shared_ptr<Circle> pauseMenuSelectedPointer (new Circle(30));
    pauseMenuSelectedPointer->set_id(PAUSE_MENU_SELECTED_POINTER);
	pauseMenuSelectedPointer->set_scale(CIRCLE_SCALE);
	pauseMenuSelectedPointer->visible(true);
	
	std::shared_ptr<Text> pauseMenuButtonResume (new Text(RESOURCES_PATH + "Font.otf"));
	pauseMenuButtonResume->set_text("Resume");
	pauseMenuButtonResume->set_color(Color(0, 0, 0));
	pauseMenuButtonResume->set_id(PAUSE_MENU_RESUME_ITEM);

	std::shared_ptr<Text> pauseMenuButtonExit (new Text(RESOURCES_PATH + "Font.otf"));
	pauseMenuButtonExit->set_text("Exit");
	pauseMenuButtonExit->set_color(Color(0, 0, 0));
	pauseMenuButtonExit->set_id(PAUSE_MENU_EXIT_ITEM);

	std::shared_ptr<Text> pauseMenuButtonTest1 (new Text(RESOURCES_PATH + "Font.otf"));
	pauseMenuButtonTest1->set_text("Test1");
	pauseMenuButtonTest1->set_color(Color(0, 0, 0));
	pauseMenuButtonTest1->set_id("TEST1");

	std::shared_ptr<Text> pauseMenuButtonTest2 (new Text(RESOURCES_PATH + "Font.otf"));
	pauseMenuButtonTest2->set_text("Test2");
	pauseMenuButtonTest2->set_color(Color(0, 0, 0));
	pauseMenuButtonTest2->set_id("TEST2");

	std::shared_ptr<Text> pauseMenuButtonTest3 (new Text(RESOURCES_PATH + "Font.otf"));
	pauseMenuButtonTest3->set_text("Test3");
	pauseMenuButtonTest3->set_color(Color(0, 0, 0));
	pauseMenuButtonTest3->set_id("TEST3");

	std::map<std::string, std::shared_ptr<Text>> pauseMenuItems{
															std::pair(pauseMenuButtonExit->get_id(), pauseMenuButtonExit), 
															std::pair(pauseMenuButtonResume->get_id(), pauseMenuButtonResume), 
															std::pair(pauseMenuButtonTest1->get_id(), pauseMenuButtonTest1), 
															std::pair(pauseMenuButtonTest2->get_id(), pauseMenuButtonTest2), 
															std::pair(pauseMenuButtonTest3->get_id(), pauseMenuButtonTest3), 
														};

	std::shared_ptr<Circle> right(new Circle(4));
	std::shared_ptr<Circle> left(new Circle(4));
	std::shared_ptr<Circle> up(new Circle(4));
	std::shared_ptr<Circle> down(new Circle(4));


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
												&prefer_menu]()
			{
				layoutDispatcher->change_layout(PAUSE_MENU);
				eventsDispatcher->change_event_handler(EVENT_PAUSE_MENU);
				auto menu = layoutDispatcher->get_layout();
				Vector2UI menuSize = menu.first->get_size();

				prefer_menu->set_pointer(menu.second.at(PAUSE_MENU_SELECTED_POINTER));
				prefer_menu->set_layout(menu.first);

				for(const auto& var : menu.second)
				{
					if(var.first == PAUSE_MENU_SELECTED_POINTER)
					{
						prefer_menu->set_pointer(var.second);
						continue;
					}

					prefer_menu->add_item(var.second);
				}

				prefer_menu->menu_configure();

				view->set_position((menuSize.x / 2), (menuSize.y / 2));
				view->set_size(menuSize.x, menuSize.y);

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


	menuEvents->add_user_event([&prefer_menu, &pauseMenuItems]
			{
				std::string item_id = prefer_menu->selected_item();

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

	menuEvents->add_key_event(Keyboard_Key::Up, [&prefer_menu]
			{
				prefer_menu->step_back();
			}, EventHandlerType::EVENT_LOOP);

	menuEvents->add_key_event(Keyboard_Key::Down, [&prefer_menu]
			{
				prefer_menu->step_forward();
			}, EventHandlerType::EVENT_LOOP);


	menuEvents->add_key_event(Keyboard_Key::Enter, [&prefer_menu,
													&layoutDispatcher,
													&eventsDispatcher,
													&core,
													&view,
													&person]
			{
				std::string selectedItem = prefer_menu->selected_item();
				if(selectedItem == PAUSE_MENU_EXIT_ITEM)
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

    window->init();
    window->set_position(500, 500);
    window->set_view(view);

	layoutDispatcher->add_layout(pauseMenu->get_id(), pauseMenu);
	layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonResume->get_id(), pauseMenuButtonResume);
	layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuSelectedPointer->get_id(), pauseMenuSelectedPointer);
	layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonExit->get_id(), pauseMenuButtonExit);
	layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonTest1->get_id(), pauseMenuButtonTest1);
	layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonTest2->get_id(), pauseMenuButtonTest2);
	layoutDispatcher->insert_layout_child(pauseMenu->get_id(), pauseMenuButtonTest3->get_id(), pauseMenuButtonTest3);

	layoutDispatcher->add_layout(mapForest->get_id(), mapForest);
	layoutDispatcher->insert_layout_child(mapForest->get_id(), person->get_id(), person);

    layoutDispatcher->add_layout(mapTower->get_id(), mapTower);
    layoutDispatcher->insert_layout_child(mapTower->get_id(), person->get_id(), person);
    layoutDispatcher->add_object(circle->get_id(), circle);
	layoutDispatcher->change_layout(mapForest->get_id());

	eventsDispatcher->register_event_handler(mainEvents->get_id(), mainEvents);
	eventsDispatcher->register_event_handler(menuEvents->get_id(), menuEvents);
	eventsDispatcher->change_event_handler(mainEvents->get_id());

    core->register_app(std::move(window));
	core->set_layout_dispatcher(layoutDispatcher);
    core->set_event_dispatcher(eventsDispatcher);
	core->run();

    return EXIT_SUCCESS;
}
