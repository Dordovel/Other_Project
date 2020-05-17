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
const static std::string NPC_FILE_NAME = "hero.png";
const static Vector2F OBJECT_SCALE = {0.2f, 0.3f};
const static Vector2F CIRCLE_SCALE = {0.2f, 0.2f};
const static std::string RESOURCES_PATH = "./Game_Resources/Image/";
const static std::map<std::string, std::pair<std::string, std::string>> MAP_PATH = 
									{
										{"menu", std::make_pair("./Game_Resources/Image/", "main_menu.tmx")},
										{"forest", std::make_pair("./Game_Resources/Image/forest/", "main.tmx")},
										{"desert", std::make_pair("./Game_Resources/Image/desert/", "tower.tmx")}
									};

int main()
{
	std::shared_ptr<Menu> prefer_menu(new Menu);

    std::unique_ptr<ICore> core (new Core);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher (new LayoutDispatcher);
	std::shared_ptr<IEventDispatcher> eventsDispatcher (new EventDispatcher);

    std::unique_ptr<IDataBase> dataBase (new DataBase(RESOURCES_PATH));

	std::pair desert = MAP_PATH.at("desert");
	std::shared_ptr<ILayout> map_tower (new Layout(desert.first, desert.second));
    map_tower->set_id(TOWER_MAP);
    
	std::pair forest = MAP_PATH.at("forest");
	std::shared_ptr<ILayout> map_forest (new Layout(forest.first, forest.second));
	map_forest->set_id(FOREST_MAP);

	std::pair menu = MAP_PATH.at("menu");
	std::shared_ptr<ILayout> main_menu (new Layout(menu.first, menu.second));
    main_menu->set_id(MAIN_MENU);

	std::shared_ptr<IPhysics> physics (new Physics);

    std::shared_ptr<IApplication> window (new Application("Test_Game", 700, 500));

    std::shared_ptr<IClock> clock (new Clock(8000));

    std::shared_ptr<Image> person (new Image(dataBase->get_resources(PersonProfession::Magic, NPC_FILE_NAME)));
    person->set_id(MAIN_PERSON);
    person->set_position(1300, 1300);
	person->set_scale(OBJECT_SCALE);

    std::shared_ptr<Circle> circle (new Circle(40));
    circle->set_id(MOUSE_POINTER);
	std::cout<<circle->get_scale()<<std::endl;
	circle->set_scale(CIRCLE_SCALE);
 	
	std::shared_ptr<Circle> menuSelectedPointer (new Circle(30));
    menuSelectedPointer->set_id(MAIN_MENU_SELECTED_POINTER);
	menuSelectedPointer->set_scale(CIRCLE_SCALE);
	menuSelectedPointer->visible(true);
	
	std::shared_ptr<Text> menuButtonResume (new Text(RESOURCES_PATH + "Font.otf"));
	menuButtonResume->set_text("Resume");
	menuButtonResume->set_color(Color(0, 0, 0));
	menuButtonResume->set_id(MAIN_MENU_RESUME_ITEM);

	std::shared_ptr<Text> menuButtonExit (new Text(RESOURCES_PATH + "Font.otf"));
	menuButtonExit->set_text("Exit");
	menuButtonExit->set_color(Color(0, 0, 0));
	menuButtonExit->set_id(MAIN_MENU_EXIT_ITEM);

    std::shared_ptr<IView> view (new View(person->get_position(), 300, 300));
    view->zoom(2);

    std::shared_ptr<IMove> mover (new Move);

    std::shared_ptr<IEvents> mainEvents (new Events);
	mainEvents->set_id(EVENT_MAP);

    mainEvents->set_close_window_event([&core](){core->close();});

    mainEvents->add_user_event([&clock](){clock->restart();});

    mainEvents->add_user_event([&physics, &layoutDispatcher, &view]()
    {
		auto current_layout = layoutDispatcher->get_layout();

		for(auto&& [id, object] : current_layout.second)
		{
			if(physics->check_collision(current_layout.first, object) != CollectionObject::NONE)
			{
				Vector2F current_position = object->get_position();
				int radius = 4;
				int value = 20;

				std::shared_ptr<Circle> right(new Circle(radius));
				right->set_position(current_position.x + 30, current_position.y + value);

				std::shared_ptr<Circle> left(new Circle(radius));
				left->set_position(current_position.x - value, current_position.y + value);

				std::shared_ptr<Circle> up(new Circle(radius));
				up->set_position(current_position.x + 4, current_position.y - value);

				std::shared_ptr<Circle> down(new Circle(radius));
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

	mainEvents->add_key_event(Keyboard_Key::I, [&layoutDispatcher, &view, &prefer_menu]()
    {
		layoutDispatcher->change_layout(MAIN_MENU);
		auto menu = layoutDispatcher->get_layout();
		Vector2UI menuSize = menu.first->get_size();

		prefer_menu->set_layout(menu.first);
		prefer_menu->add_item(menu.second.at(MAIN_MENU_RESUME_ITEM));
		prefer_menu->add_item(menu.second.at(MAIN_MENU_EXIT_ITEM));
		prefer_menu->menu_configure();

		view->set_position((menuSize.x / 2), (menuSize.y / 2));
		view->set_size(menuSize.x, menuSize.y);

    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::D, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::RIGHT, person, clock->get_time(), SPEED);
        mover->move(SIDE::RIGHT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Escape, [&core]()
    {
        core->close();
    }, EventHandlerType::EVENT_LOOP);

    mainEvents->add_key_event(Keyboard_Key::A, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::LEFT, person, clock->get_time(), SPEED);
        mover->move(SIDE::LEFT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::S, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::DOWN, person, clock->get_time(), SPEED);
        mover->move(SIDE::DOWN, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::W, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::UP, person, clock->get_time(), SPEED);
        mover->move(SIDE::UP, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);


    mainEvents->add_key_event(Keyboard_Key::Right, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::RIGHT, person, clock->get_time(), SPEED);
        mover->move(SIDE::RIGHT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Left, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::LEFT, person, clock->get_time(), SPEED);
        mover->move(SIDE::LEFT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Down, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::DOWN, person, clock->get_time(), SPEED);
        mover->move(SIDE::DOWN, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Up, [&mover, &person, &clock, &view]()
    {
        mover->move(SIDE::UP, person, clock->get_time(), SPEED);
        mover->move(SIDE::UP, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);


    window->init();
    window->set_position(500, 500);
    window->set_view(view);

	layoutDispatcher->add_layout(main_menu->get_id(), main_menu);
	layoutDispatcher->insert_layout_child(main_menu->get_id(), menuButtonResume->get_id(), menuButtonResume);
	layoutDispatcher->insert_layout_child(main_menu->get_id(), menuSelectedPointer->get_id(), menuSelectedPointer);
	layoutDispatcher->insert_layout_child(main_menu->get_id(), menuButtonExit->get_id(), menuButtonExit);

	layoutDispatcher->add_layout(map_forest->get_id(), map_forest);
	layoutDispatcher->insert_layout_child(map_forest->get_id(), person->get_id(), person);

    layoutDispatcher->add_layout(map_tower->get_id(), map_tower);
    layoutDispatcher->insert_layout_child(map_tower->get_id(), person->get_id(), person);
    layoutDispatcher->add_object(circle->get_id(), circle);
	layoutDispatcher->change_layout(map_forest->get_id());

	eventsDispatcher->register_event_handler(mainEvents->get_id(), mainEvents);
	eventsDispatcher->change_event_handler(mainEvents->get_id());

    core->register_app(std::move(window));
	core->set_layout_dispatcher(layoutDispatcher);
    core->set_event_dispatcher(eventsDispatcher);
	core->run();

    return EXIT_SUCCESS;
}
