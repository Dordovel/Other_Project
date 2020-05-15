#include "./struct/rectobject.hpp"
#include "./struct/vectorobject.hpp"
#include "./headers/core.hpp"
#include "./headers/application.hpp"
#include "./headers/layout.hpp"
#include "./headers/events.hpp"
#include "./headers/database.hpp"
#include "./headers/clock.hpp"
#include "./graphicobject/person.hpp"
#include "./headers/physics.hpp"
#include "./headers/compass.hpp"
#include "./headers/view.hpp"
#include "./graphicobject/circle.hpp"
#include "./algorithm/move.hpp"
#include "./headers/event_dispatcher.hpp"
#include "./headers/layout_dispatcher.hpp"
#include "./graphicobject/text.hpp"

constexpr int SPEED = 2;
const static std::string RESOURCES_PATH = "./Game_Resources/Image/";
const static std::map<std::string, std::pair<std::string, std::string>> MAP_PATH = 
									{
										{"menu", std::make_pair("./Game_Resources/Image/", "main_menu.tmx")},
										{"forest", std::make_pair("./Game_Resources/Image/forest/", "main.tmx")},
										{"desert", std::make_pair("./Game_Resources/Image/desert/", "tower.tmx")}
									};

const static std::string NPC_FILE_NAME = "hero.png";
const static Vector2F OBJECT_SCALE = {0.2f, 0.3f}; 

int main()
{
    std::unique_ptr<ICore> core (new Core);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher (new LayoutDispatcher);
	std::shared_ptr<IEventDispatcher> eventsDispatcher (new EventDispatcher);

    std::unique_ptr<IDataBase> dataBase (new DataBase(RESOURCES_PATH));

	std::pair desert = MAP_PATH.at("desert");
	std::shared_ptr<ILayout> map_desert (new Layout(desert.first, desert.second));
    map_desert->set_id("Desert_Map");
    
	std::pair forest = MAP_PATH.at("forest");
	std::shared_ptr<ILayout> map_forest (new Layout(forest.first, forest.second));
	map_forest->set_id("Forest_Map");

	std::pair menu = MAP_PATH.at("menu");
	std::shared_ptr<ILayout> main_menu (new Layout(menu.first, menu.second));
    main_menu->set_id("Main_Menu");

	std::shared_ptr<IPhysics> physics (new Physics);

    std::shared_ptr<IApplication> window (new Application("Test_Game", 700, 500));

    std::shared_ptr<IClock> clock (new Clock(8000));

    std::shared_ptr<Person> person (new Person(dataBase->get_resources(PersonProfession::Magic, NPC_FILE_NAME)));
    person->set_id("Main_Person");
    person->set_position(1300, 1300);
	person->set_scale(OBJECT_SCALE);

    std::shared_ptr<Circle> circle (new Circle(40));
    circle->set_id("Mouse_Pointer");
	circle->set_scale(OBJECT_SCALE);

	std::shared_ptr<Text> test (new Text(RESOURCES_PATH + "Font.otf"));
	test->set_text("TEST");
	test->set_color(Color(0, 0, 0));
	test->set_position(main_menu->get_size().x / 2, main_menu->get_size().y / 2);

    std::shared_ptr<IView> view (new View(person->get_position(), 300, 300));
    view->zoom(2);

    std::shared_ptr<IMove> mover (new Move);

    std::shared_ptr<IEvents> mainEvents (new Events);
	mainEvents->set_id("Main_Events");

    mainEvents->set_close_window_event([&core](){core->close();});

    mainEvents->add_user_event([&clock](){clock->restart();});

    mainEvents->add_user_event([&physics, &person, &layoutDispatcher, &mover]()
    {
		auto current_layout = layoutDispatcher->get_layout().first;

		Compass compass(current_layout->get_size());
        CompassSide side = compass.get_compass_side(person->get_position().x,
                                            person->get_position().y);

        if(physics->check_collision(current_layout, person, {CollectionObject::BORDER}))
        {
			if(side != CompassSide::Stand)
			{
				if(side == CompassSide::North)
				{
					mover->block_side(MoveSide::UP, true);
				}

				if(side == CompassSide::West)
				{
					mover->block_side(MoveSide::LEFT, true);
				}

				if(side == CompassSide::East)
				{
					mover->block_side(MoveSide::RIGHT, true);	
				}

				if(side == CompassSide::South)
				{
					mover->block_side(MoveSide::DOWN, true);
				}
			}
		}
		else
		{
			mover->block_side(MoveSide::LEFT, false);
			mover->block_side(MoveSide::UP, false);
			mover->block_side(MoveSide::RIGHT, false);
			mover->block_side(MoveSide::DOWN, false);
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

	mainEvents->add_key_event(Keyboard_Key::I, [&layoutDispatcher, &view]()
    {
		layoutDispatcher->change_layout("Main_Menu");
		auto menu = layoutDispatcher->get_layout();
		Vector2UI menuSize = menu.first->get_size();

		view->set_position((menuSize.x / 2), (menuSize.y / 2));
		view->set_size(menuSize.x, menuSize.y);

    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::D, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::RIGHT, person, clock->get_time(), SPEED);
        mover->move(MoveSide::RIGHT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Escape, [&core]()
    {
        core->close();
    }, EventHandlerType::EVENT_LOOP);

    mainEvents->add_key_event(Keyboard_Key::A, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::LEFT, person, clock->get_time(), SPEED);
        mover->move(MoveSide::LEFT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::S, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::DOWN, person, clock->get_time(), SPEED);
        mover->move(MoveSide::DOWN, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::W, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::UP, person, clock->get_time(), SPEED);
        mover->move(MoveSide::UP, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);


    mainEvents->add_key_event(Keyboard_Key::Right, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::RIGHT, person, clock->get_time(), SPEED);
        mover->move(MoveSide::RIGHT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Left, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::LEFT, person, clock->get_time(), SPEED);
        mover->move(MoveSide::LEFT, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Down, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::DOWN, person, clock->get_time(), SPEED);
        mover->move(MoveSide::DOWN, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Up, [&mover, &person, &clock, &view]()
    {
        mover->move(MoveSide::UP, person, clock->get_time(), SPEED);
        mover->move(MoveSide::UP, view, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);


    window->init();
    window->set_position(500, 500);
    window->set_view(view);

	layoutDispatcher->add_layout(main_menu->get_id(), main_menu);
	layoutDispatcher->insert_layout_child(main_menu->get_id(), test->get_id(), test);

	layoutDispatcher->add_layout(map_forest->get_id(), map_forest);
	layoutDispatcher->insert_layout_child(map_forest->get_id(), person->get_id(), person);

    layoutDispatcher->add_layout(map_desert->get_id(), map_desert);
    layoutDispatcher->insert_layout_child(map_desert->get_id(), person->get_id(), person);
    layoutDispatcher->add_object(circle->get_id(), circle);
	layoutDispatcher->change_layout(map_desert->get_id());

	eventsDispatcher->register_event_handler(mainEvents->get_id(), mainEvents);
	eventsDispatcher->change_event_handler(mainEvents->get_id());

    core->register_app(std::move(window));
	core->set_layout_dispatcher(layoutDispatcher);
    core->set_event_dispatcher(eventsDispatcher);
    core->run();

    return EXIT_SUCCESS;
}
