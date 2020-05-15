#include "./struct/rectobject.hpp"
#include "./struct/vectorobject.hpp"
#include "./headers/core.hpp"
#include "./headers/application.hpp"
#include "./headers/gamemapdesert.hpp"
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

constexpr int SPEED = 2;
const static std::string RESOURCES_PATH = "./Game_Resources/Image/test/";
const static std::string NPC_FILE_NAME = "hero.png";
const static Vector2F OBJECT_SCALE = {0.3f, 0.3f}; 

int main()
{
    std::unique_ptr<ICore> core (new Core);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher (new LayoutDispatcher);
	std::shared_ptr<IEventDispatcher> eventsDispatcher (new EventDispatcher);

    std::unique_ptr<IDataBase> dataBase (new DataBase(RESOURCES_PATH));

    std::shared_ptr<IMap> map (new GameMapDesert(RESOURCES_PATH, "main.tmx"));
    map->set_id("Desert_Map");

    std::shared_ptr<IPhysics> physics (new Physics);

    std::shared_ptr<IApplication> window (new Application("Test_Game", 700, 500));

    std::shared_ptr<IClock> clock (new Clock(8000));

    std::shared_ptr<Person> person (new Person(dataBase->get_resources(PersonProfession::Magic, NPC_FILE_NAME)));
    person->set_id("Main_Person");
    person->set_position(1300, 1300);
	person->set_scale(OBJECT_SCALE);

    std::shared_ptr<Circle> circle (new Circle(40));
    circle->set_id("Mouse_Pointer");

    std::shared_ptr<IView> view (new View(person->get_position(), 200, 200));
    view->zoom(2);

    Compass compass(map->get_map_size_x(), map->get_map_size_y());

    std::shared_ptr<IMove> mover (new Move);


    std::shared_ptr<IEvents> mainEvents (new Events);
	mainEvents->set_id("Main_Events");

    mainEvents->set_close_window_event([&core](){core->close();});

    mainEvents->add_user_event([&clock](){clock->restart();});

    mainEvents->add_user_event([&view, &person]()
    {
        view->set_position(person->get_position());
    });

    mainEvents->add_user_event([&physics, &person, &compass, &map, &mover]()
    {
        CompassSide side = compass.get_compass_side(person->get_position().x,
                                            person->get_position().y);

        if(physics->check_collision(map, person, {CollectionObject::BORDER}))
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
                                                   &map,
                                                   &clock](int X, int Y)
     {
        Vector2F coordinates = window->map_pixel_to_coords(X, Y);
        circle->visible(true);
        circle->set_position(coordinates);
        mover->move(person, clock, physics, map, coordinates, SPEED);
     });

    mainEvents->mouse_button_released([&circle](){circle->visible(false);});


    mainEvents->add_key_event(Keyboard_Key::D, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::RIGHT, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Escape, [&core]()
    {
        core->close();
    }, EventHandlerType::EVENT_LOOP);

    mainEvents->add_key_event(Keyboard_Key::A, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::LEFT, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::S, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::DOWN, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::W, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::UP, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);


    mainEvents->add_key_event(Keyboard_Key::Right, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::RIGHT, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Left, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::LEFT, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Down, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::DOWN, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);

    mainEvents->add_key_event(Keyboard_Key::Up, [&mover, &person, &clock]()
    {
        mover->move(MoveSide::UP, person, clock->get_time(), SPEED);
    }, EventHandlerType::NONE);


    window->init();
    window->set_position(500, 500);
    window->set_view(view);

    layoutDispatcher->add_layout(map->get_id(), map);
    layoutDispatcher->insert_layout_child(map->get_id(), person->get_id(), person);
    layoutDispatcher->add_object(circle->get_id(), circle);
	layoutDispatcher->change_layout(map->get_id());

	eventsDispatcher->register_event_handler(mainEvents->get_id(), mainEvents);
	eventsDispatcher->change_event_handler(mainEvents->get_id());

    core->register_app(std::move(window));
	core->set_layout_dispatcher(layoutDispatcher);
    core->set_event_dispatcher(eventsDispatcher);
    core->run();

    return EXIT_SUCCESS;
}
