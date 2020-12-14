#include "./headers/application.hpp"
#include "./headers/layout.hpp"
#include "./headers/keyboard_unit.hpp"
#include "./headers/mouse_unit.hpp"
#include "./headers/database.hpp"
#include "./headers/clock.hpp"
#include "./graphicobject/sprite.hpp"
#include "./headers/view.hpp"
#include "./graphicobject/circle.hpp"
#include "./algorithm/move.hpp"
#include "./menu_builder.hpp"
#include "./graphicobject/rectangle.hpp"
#include "./headers/collision.hpp"
#include "./headers/quest_npc.hpp"
#include "./headers/damage_generator.hpp"
#include "./headers/npc_dispatcher.hpp"
#include "./headers/npc.hpp"
#include "./headers/chest_dispatcher.hpp"
#include "./headers/chest.hpp"
#include <chrono>

using namespace PROJECT;
using namespace std::literals;

std::shared_ptr<BASE::GRAPHIC::IRectangle> create_test_inventory(std::string id, float width, float height, BASE::GRAPHIC::Color color)
{
	std::shared_ptr<BASE::GRAPHIC::IRectangle> inventoryItem;
	inventoryItem = std::make_shared<BASE::GRAPHIC::Rectangle>(width, height);
	inventoryItem->set_color(color);
	inventoryItem->set_id(id);

	return inventoryItem;
}


float convert_value(int lv, int rv, float value)
{
	return (rv * ((value / lv) * 100)) / 100;
}

std::unique_ptr<CHEST::IChest> make_chest(const DATABASE::IDataBase& dataBase)
{
	std::unique_ptr<CHEST::IChest> chest = 
			std::make_unique<CHEST::Chest>(dataBase.get_resources("ChestRed.png", {0, 0, 24, 24}));
	chest->set_scale({chest->get_scale().x - 0.2F, chest->get_scale().y + 0.2F});

	return chest;
}

MOVE::Side inversion_side(MOVE::Side side)
{
	if(side == MOVE::Side::UP)
	{
		return MOVE::Side::DOWN;
	}

	if(side == MOVE::Side::DOWN)
	{
		return MOVE::Side::UP;
	}

	if(side == MOVE::Side::LEFT)
	{
		return MOVE::Side::RIGHT;
	}

	if(side == MOVE::Side::RIGHT)
	{
		return MOVE::Side::LEFT;
	}

	return MOVE::Side::NONE;
}

std::array<std::pair<std::string, std::string>, 4>
open_select_menu(std::string_view lastItem) noexcept
{
	std::array<std::pair<std::string, std::string>, 4> generateItem;
	
	if(lastItem == NPC_JEREMY_TYPE_ITEM)
	{
		generateItem[0] = std::pair(NPC_JEREMY_PINK, "Pink"sv);
		generateItem[1] = std::pair(NPC_JEREMY_GREEN, "Green"sv);
		generateItem[2] = std::pair(NPC_JEREMY_BLONDE, "Blonde"sv);
	}
	else if(lastItem == NPC_MARTHA_TYPE_ITEM)
	{
		generateItem[0] = std::pair(NPC_MARTHA_PINK, "Pink"sv);
		generateItem[1] = std::pair(NPC_MARTHA_GREEN, "Green"sv);
		generateItem[2] = std::pair(NPC_MARTHA_BLONDE, "Blonde"sv);
	}

	generateItem[3] = std::pair(MENU_BACK_ITEM, "Back"sv);

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 3>
open_type_menu() noexcept
{
	std::array<std::pair<std::string, std::string>, 3> generateItem;

	generateItem[0] = std::pair(NPC_JEREMY_TYPE_ITEM, "Jeremy"sv);
	generateItem[1] = std::pair(NPC_MARTHA_TYPE_ITEM, "Martha"sv);
	generateItem[2] = std::pair(MENU_BACK_ITEM, "Back"sv);

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 2>
open_main_menu() noexcept
{
	std::array<std::pair<std::string, std::string>, 2> generateItem;

	generateItem[0] = std::pair(MAIN_MENU_START_ITEM, "New"sv);
	generateItem[1] = std::pair(MENU_EXIT_ITEM, "Exit"sv);

	return generateItem;
}

std::array<std::pair<std::string, std::string>, 2>
open_pause_menu() noexcept
{
	std::array<std::pair<std::string, std::string>, 2> generateItem;

	generateItem[0] = std::pair(PAUSE_MENU_RESUME_ITEM, "Resume"sv);
	generateItem[1] = std::pair(MENU_EXIT_ITEM, "Main Menu"sv);

	return generateItem;
}

std::unique_ptr<NPC::Npc> change_person_type(std::string_view type, const DATABASE::IDataBase& dataBase) noexcept

{
	std::unique_ptr<NPC::Npc> result = nullptr;

	if(type == NPC_JEREMY_PINK)
	{
		result = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_PINK, MOVE::Side::DOWN));
	}

	else if(type == NPC_MARTHA_PINK)
	{
		result = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_PINK, MOVE::Side::DOWN));
	}

	else if(type == NPC_JEREMY_GREEN)
	{
		result = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_GREEN, MOVE::Side::DOWN));
	}

	else if(type == NPC_MARTHA_GREEN)
	{
		result = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_GREEN, MOVE::Side::DOWN));
	}

	else if(type == NPC_JEREMY_BLONDE)
	{
		result = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_BLONDE, MOVE::Side::DOWN));
	}

	else if(type == NPC_MARTHA_BLONDE)
	{
		result = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_BLONDE, MOVE::Side::DOWN));
	}

	return result;
}	

enum class MenuType
{
	MAIN,
	PAUSE
};


PROJECT::BASE::DATA::Vector2F get_object_center_position(const STATIC* const object)
{
	PROJECT::BASE::DATA::RectangleF rect = object->get_global_bounds();
	
	return {rect.left + (rect.width / 2), rect.top + (rect.height / 2)};
}

PROJECT::BASE::DATA::Vector2F 
	adapt_view_position(const PROJECT::BASE::DATA::Vector2F& viewCenterPointer,
							const PROJECT::BASE::DATA::Vector2F& viewSize)
{

	float viewCenterX = viewSize.x / 2;
	float viewCenterY = viewSize.y / 2;

	return {viewCenterPointer.x - viewCenterX, viewCenterPointer.y - viewCenterY};
}

std::string menu(MenuType type,
				std::shared_ptr<APPLICATION::IApplication> app,
				std::shared_ptr<APPLICATION::IView> view) noexcept
{	
	std::shared_ptr<BASE::GRAPHIC::Rectangle> menuSelectedPointer =
			std::make_shared<BASE::GRAPHIC::Rectangle>(8, 20);
	menuSelectedPointer->visible(true);
	menuSelectedPointer->set_color(PROJECT::BASE::GRAPHIC::Color::Purple);
	
	std::string result;

	std::shared_ptr<PROJECT::BASE::GRAPHIC::IRectangle> layout = 
			std::make_shared<PROJECT::BASE::GRAPHIC::Rectangle>(view->get_size());
	layout->set_position(adapt_view_position(view->get_position(), view->get_size()));
	layout->set_color(PROJECT::BASE::GRAPHIC::Color::Black);

	if(type == MenuType::MAIN)
	{
		bool isMainMenu = true;
		bool isSecondMenu = true;

		while(isMainMenu)
		{
			result = menu_builder(app, menuSelectedPointer, layout, open_main_menu());

			if(result == MAIN_MENU_START_ITEM)
			{
				while(isSecondMenu)
				{
					result = menu_builder(app, menuSelectedPointer, layout, open_type_menu());

					if(result == MENU_BACK_ITEM)
					{
						break;
					}

					if(result == EXIT)
					{
						isMainMenu = false;
						isSecondMenu = false;
					}
					else
					{
						result = menu_builder(app, menuSelectedPointer, layout, open_select_menu(result));
						
						if(result == MENU_BACK_ITEM)
						{
							continue;
						}

						isMainMenu = false;
						isSecondMenu = false;
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
		result = menu_builder(app, menuSelectedPointer, layout, open_pause_menu());
	}

	return result;
}

int main()
{
    std::shared_ptr<APPLICATION::View> view = std::make_shared<APPLICATION::View>();
	view->set_position(DEFAULT_POSITION);
	view->set_size(DEFAULT_VIEW_SIZE);
	view->zoom(DEFAULT_VIEW_ZOOM);

    std::shared_ptr<APPLICATION::Application> app =
			std::make_shared<APPLICATION::Application>("Test_Project", 700, 500);
    app->init();
    app->set_position(500, 500);
	app->set_view(view);

    DATABASE::DataBase dataBase(RESOURCES_PATH);

	CLOCK::Clock clock;

	ANIMATION::Anim anim(ANIMATION_FRAME);

	bool isOpen = true; 
	bool isRun = true; 


	while(isOpen)
	{
		 //std::string result = menu(MenuType::MAIN, app, view);
		 //if(result == MENU_EXIT_ITEM || result == EXIT)
		 //{
		 //	app->close();
		 //	break;
		 //}

		std::shared_ptr<NPC::Npc> person = nullptr;
		//person = change_person_type(result, dataBase);
		person = std::make_unique<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_PINK, MOVE::Side::DOWN));
		person->set_position(DEFAULT_POSITION);
		person->set_scale(OBJECT_SCALE);
		person->set_max_health(200);
		person->set_health(person->get_max_health());
		person->set_damage(100);
		person->set_state(NPC::State::IDLE);

		std::unique_ptr<NPC::Npc> personTest = nullptr;
		personTest = change_person_type(NPC_JEREMY_GREEN, dataBase);
		personTest->set_position(1230, 1200);
		personTest->set_scale(OBJECT_SCALE);
		personTest->set_max_health(5);
		personTest->set_health(personTest->get_max_health());
		personTest->set_damage(10);
		personTest->set_id("TEST");

		std::unique_ptr<NPC::Npc> personTest1 = nullptr;
		personTest1 = change_person_type(NPC_MARTHA_GREEN, dataBase);
		personTest1->set_position(1170, 1200);
		personTest1->set_scale(OBJECT_SCALE);
		personTest1->set_max_health(5);
		personTest1->set_health(personTest1->get_max_health());
		personTest1->set_damage(10);
		personTest1->set_id("TEST1");

		person->add_animation_walk(MOVE::Side::RIGHT, dataBase.get_animation_walk(MOVE::Side::RIGHT));
		person->add_animation_walk(MOVE::Side::LEFT, dataBase.get_animation_walk(MOVE::Side::LEFT));
		person->add_animation_walk(MOVE::Side::DOWN, dataBase.get_animation_walk(MOVE::Side::DOWN));
		person->add_animation_walk(MOVE::Side::UP, dataBase.get_animation_walk(MOVE::Side::UP));
		person->add_animation_walk(MOVE::Side::NONE, dataBase.get_animation_walk(MOVE::Side::DOWN));

		person->add_animation_attack(MOVE::Side::RIGHT, dataBase.get_animation_attack(MOVE::Side::RIGHT));
		person->add_animation_attack(MOVE::Side::LEFT, dataBase.get_animation_attack(MOVE::Side::LEFT));
		person->add_animation_attack(MOVE::Side::DOWN, dataBase.get_animation_attack(MOVE::Side::DOWN));
		person->add_animation_attack(MOVE::Side::UP, dataBase.get_animation_attack(MOVE::Side::UP));


		
		personTest->add_animation_walk(MOVE::Side::RIGHT, dataBase.get_animation_walk(MOVE::Side::RIGHT));
		personTest->add_animation_walk(MOVE::Side::LEFT, dataBase.get_animation_walk(MOVE::Side::LEFT));
		personTest->add_animation_walk(MOVE::Side::DOWN, dataBase.get_animation_walk(MOVE::Side::DOWN));
		personTest->add_animation_walk(MOVE::Side::UP, dataBase.get_animation_walk(MOVE::Side::UP));

		personTest->add_animation_attack(MOVE::Side::RIGHT, dataBase.get_animation_attack(MOVE::Side::RIGHT));
		personTest->add_animation_attack(MOVE::Side::LEFT, dataBase.get_animation_attack(MOVE::Side::LEFT));
		personTest->add_animation_attack(MOVE::Side::DOWN, dataBase.get_animation_attack(MOVE::Side::DOWN));
		personTest->add_animation_attack(MOVE::Side::UP, dataBase.get_animation_attack(MOVE::Side::UP));



		personTest1->add_animation_walk(MOVE::Side::RIGHT, dataBase.get_animation_walk(MOVE::Side::RIGHT));
		personTest1->add_animation_walk(MOVE::Side::LEFT, dataBase.get_animation_walk(MOVE::Side::LEFT));
		personTest1->add_animation_walk(MOVE::Side::DOWN, dataBase.get_animation_walk(MOVE::Side::DOWN));
		personTest1->add_animation_walk(MOVE::Side::UP, dataBase.get_animation_walk(MOVE::Side::UP));

		personTest1->add_animation_attack(MOVE::Side::RIGHT, dataBase.get_animation_attack(MOVE::Side::RIGHT));
		personTest1->add_animation_attack(MOVE::Side::LEFT, dataBase.get_animation_attack(MOVE::Side::LEFT));
		personTest1->add_animation_attack(MOVE::Side::DOWN, dataBase.get_animation_attack(MOVE::Side::DOWN));
		personTest1->add_animation_attack(MOVE::Side::UP, dataBase.get_animation_attack(MOVE::Side::UP));

		MOVE::Side personMoveSide = MOVE::Side::NONE;
		MOVE::Side randMoveSide = MOVE::Side::DOWN;
		bool showInventory = false;
		bool MOUSE_SINGLE_PRESSED = false;
		bool MOUSE_SINGLE_PRESSED_1 = false;
		bool MOUSE_PRESSED = false;
		BASE::DATA::Vector2I MOUSE_BUTTON_PRESS_COORDS;

		std::pair forest = MAP_PATH.at("forest");
		std::unique_ptr<COLLECTION::Layout> mapForest =
				std::make_unique<COLLECTION::Layout>(forest.first, forest.second);

		std::unique_ptr<MOVE::Move> mover = std::make_unique<MOVE::Move>();

		UNIT::CONTROL::KEYBOARD::KeyboardUnit keyboard;
		UNIT::CONTROL::MOUSE::MouseUnit mouse;

		COLLISION::Collision collision;
		PHYSICS::Physics physics;


		mouse.button_pressed(UNIT::CONTROL::MOUSE::Mouse_Key::Left, [&MOUSE_BUTTON_PRESS_COORDS,
																		&MOUSE_PRESSED](int x, int y)
				{
					MOUSE_BUTTON_PRESS_COORDS.x = x;
					MOUSE_BUTTON_PRESS_COORDS.y = y;

					MOUSE_PRESSED = true;
				});

		mouse.button_released(UNIT::CONTROL::MOUSE::Mouse_Key::Left, [&MOUSE_BUTTON_PRESS_COORDS,
																		&MOUSE_PRESSED]()
				{
					MOUSE_BUTTON_PRESS_COORDS.x = 0;
					MOUSE_BUTTON_PRESS_COORDS.y = 0;

					MOUSE_PRESSED = false;
				});

		keyboard.set_close_window_event([&app, &isRun, &isOpen]()
				{
					app->window_close();
					isRun = false;
					isOpen = false;
				});

		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Escape, [&app,
																				&view,
																				&person,
																				&isRun]()
				{
					view->unblock_all_side();
					std::string result = menu(MenuType::PAUSE, app, view);
					if(result == PAUSE_MENU_RESUME_ITEM)
					{
						view->set_position(person->get_position());
						view->set_size(DEFAULT_VIEW_SIZE);
						view->zoom(DEFAULT_VIEW_ZOOM);
					}
					else
					{
						isRun = false;
					}
				}, UNIT::CONTROL::EventHandlerType::EVENT_LOOP);

		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::E, [&person]()
				{
					person->set_state(NPC::State::ATTACK);
				}, UNIT::CONTROL::EventHandlerType::NONE);

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::E, [&person]()
				{
					person->set_state(NPC::State::IDLE);
				});


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::F, [&showInventory]()
				{
					if(!showInventory)
						showInventory = true;
					else
						showInventory = false;
				}, UNIT::CONTROL::EventHandlerType::EVENT_LOOP);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::D, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::RIGHT;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::A, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::LEFT;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::S, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::DOWN;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::W, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::UP;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Right, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::RIGHT;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Left, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::LEFT;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Down, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::DOWN;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_pressed(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Up, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::UP;
				}, UNIT::CONTROL::EventHandlerType::NONE);


		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::D, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::A, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::S, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::W, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Right, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Left, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Down, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		keyboard.button_released(UNIT::CONTROL::KEYBOARD::Keyboard_Key::Up, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		const int PROGRESSBARWidth = 115;
		const int PROGRESSBARHeight = 25;
		const BASE::DATA::Vector2F SPRITEScale = {0.3, 0.3};

		std::unique_ptr<BASE::GRAPHIC::IRectangle> personHealth;
		personHealth = std::make_unique<BASE::GRAPHIC::Rectangle>(PROGRESSBARWidth, PROGRESSBARHeight);
		personHealth->set_color(BASE::GRAPHIC::Color::Red);
		std::unique_ptr<BASE::GRAPHIC::Text> personHealthStatus = 
				std::make_unique<BASE::GRAPHIC::Text>(RESOURCES_PATH + "Font.otf");
		personHealthStatus->visible(false);
		personHealthStatus->set_font_size(15);
		personHealthStatus->set_color(BASE::GRAPHIC::Color::Black);

		std::unique_ptr<BASE::GRAPHIC::Sprite> personHealthBackground =
				std::make_unique<BASE::GRAPHIC::Sprite>(dataBase.get_resources("healthPanel.png", 
																				{0, 0, 450, 150}));
		personHealthBackground->set_scale(SPRITEScale);


		std::unique_ptr<BASE::GRAPHIC::IRectangle> enemyHealth;
		enemyHealth	= std::make_unique<BASE::GRAPHIC::Rectangle>(PROGRESSBARWidth, PROGRESSBARHeight);
		enemyHealth->set_color(BASE::GRAPHIC::Color::Purple);
		enemyHealth->visible(false);

		std::unique_ptr<BASE::GRAPHIC::Text> enemyHealthStatus =
				std::make_unique<BASE::GRAPHIC::Text>(RESOURCES_PATH + "Font.otf");
		enemyHealthStatus->visible(false);
		enemyHealthStatus->set_font_size(15);
		enemyHealthStatus->set_color(BASE::GRAPHIC::Color::Black);

		std::unique_ptr<BASE::GRAPHIC::Sprite> enemyHealthBackground = 
				std::make_unique<BASE::GRAPHIC::Sprite>(dataBase.get_resources("healthPanel.png", {0, 0, 450, 150}));

		enemyHealthBackground->set_scale(SPRITEScale);


		float time;
		auto currentLayout = std::move(mapForest);
		NPC::DamageGenerator damage;
		damage.set_frame_time(5.F);


//VARIABLE FOR USE IN LOOP

		BASE::DATA::RectangleF loopRect = {};
		BASE::DATA::RectangleF loopRectSecond = {};
		BASE::DATA::Vector2F loopVec = {};
		BASE::DATA::Vector2F loopVecSecond = {};
		size_t loopContainerIter = 0;
		size_t loopContainerSize = 0;
		MOVE::Side personLastSide = MOVE::Side::NONE;


		std::vector<std::pair<MOVE::Side, std::string>> loopCollisionObjectList;
		std::vector<std::pair<MOVE::Side, std::shared_ptr<NPC::INpc>>> loopNpcCollisionList;

		std::vector<std::pair<MOVE::Side, std::shared_ptr<CHEST::IChest>>> loopChestCollisionList;

//END VARIABLE FOR USE IN LOOP

//VISUAL OBJECT

        DISPATCHER::NpcDispatcher npcDispatcher;
        npcDispatcher.add_object(std::move(personTest));
        npcDispatcher.add_object(std::move(personTest1));

		DISPATCHER::ChestDispatcher chestDispatcher;
		std::unique_ptr<BASE::GRAPHIC::IRectangle> chestBackground = std::make_unique<BASE::GRAPHIC::Rectangle>(100, 115);

        std::vector<std::shared_ptr<NPC::QuestNpc>> questObjectList;
        questObjectList.reserve(1);

		std::unique_ptr<BASE::GRAPHIC::IRectangle> inventoryBack;
		inventoryBack = std::make_unique<BASE::GRAPHIC::Rectangle>(100, 100);
		inventoryBack->set_color(BASE::GRAPHIC::Color::Orange);

		std::unique_ptr<BASE::GRAPHIC::ISprite> arrayNext = std::make_unique<BASE::GRAPHIC::Sprite>(dataBase.get_resources("arrayNext.png", {0, 0, 24, 24}));
		arrayNext->set_scale({0.6, 0.6});
		std::unique_ptr<BASE::GRAPHIC::ISprite> arrayBack = std::make_unique<BASE::GRAPHIC::Sprite>(dataBase.get_resources("arrayBack.png", {0, 0, 24, 24}));
		arrayBack->set_scale({0.6, 0.6});

//END VISUAL OBJECT

		while (app->is_open() && isRun)
		{
//EVENT HANDLER

			while (app->check_events())
			{
			    keyboard.catch_events(app->event_handler());
				mouse.catch_events(app->event_handler());
			}
			keyboard.catch_events();

//END EVENT HANDLER

			clock.restart();
			time = clock.get_work_time();

//DRAW LAYOUT

			app->draw(currentLayout.get());

//END DRAW LAYOUT


			if(MOUSE_PRESSED)
			{
				if(MOUSE_SINGLE_PRESSED)
				{
					MOUSE_SINGLE_PRESSED = false;
				}

				if(!MOUSE_SINGLE_PRESSED_1)
				{
					MOUSE_SINGLE_PRESSED = true;
					MOUSE_SINGLE_PRESSED_1 = true;
				}
			}
			else
			{
				MOUSE_SINGLE_PRESSED = false;
				MOUSE_SINGLE_PRESSED_1 = false;
			}


//RUN ANIMATION

			anim.run(time * DELAY);

			loopContainerSize = npcDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				npcDispatcher.animation(loopContainerIter).run(time * DELAY);
			}

//END RUN ANIMATION


//POSITIONING HEALTH BAR AND UPDATE VALUE

			loopRect = view->get_global_bounds();

			personHealth->set_position((loopRect.left + PROGRESSBARHeight),
										((loopRect.top + loopRect.height) - (PROGRESSBARHeight * 2)));

			float health = convert_value(person->get_max_health(),
													PROGRESSBARWidth,
													person->get_health());
									
			if(health < 0) health = 0;

			personHealth->set_size(health, PROGRESSBARHeight); 

			loopVec = personHealth->get_position();

			personHealthBackground->set_position((loopVec.x - 10), (loopVec.y - 10));

			personHealthStatus->set_position(personHealth->get_position()
                                                + BASE::DATA::Vector2F(10, 0));
            
			personHealthStatus->set_text(std::to_string(person->get_health()) + "/"
                                            + std::to_string(person->get_max_health()));


			loopRect = view->get_global_bounds();

			enemyHealth->set_position((loopRect.left + (loopRect.width * 0.5F) - (PROGRESSBARWidth * 0.5F)),
										(loopRect.top + PROGRESSBARHeight));

			loopVec = enemyHealth->get_position();

			enemyHealthBackground->set_position((loopVec.x - 10), (loopVec.y - 10));
            
			enemyHealthStatus->set_position(enemyHealth->get_position()
                                                + BASE::DATA::Vector2F(10, 0));
            
//END POSITIONING HEALTH BAR


//CHECK PERSON INTERACTIOIN WITH MAP OBJECT

			person->unblock_all_side();
			view->unblock_all_side();

            loopCollisionObjectList = collision.check_object_collision(currentLayout.get(), person.get());
			if(!loopCollisionObjectList.empty())
			{
				loopContainerSize = loopCollisionObjectList.size();
				for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
				{
					auto&& value = loopCollisionObjectList.at(loopContainerIter);
					person->block_side(value.first, true);
					view->block_side(value.first, true);
				}
			}

//END CHECK PERSON INTERACTIOIN WITH MAP OBJECT

			if(!chestDispatcher.empty())
			{
				loopContainerSize = chestDispatcher.size();
				for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
				{
					auto&& chest = chestDispatcher.object(loopContainerIter);

					if(!physics.check_intersection(view.get(), chest.get()))
					{
						chest->visible(false);
					}
					else
					{
						chest->visible(true);
					}

//CHECK PERSON INTERACTIOIN WITH CHEST

					if(chest->is_visible())
					{
						auto&& intersectsSide = collision.check_object_collision(person.get(), chest.get());
						
						if(intersectsSide.first != MOVE::Side::NONE)
						{
							loopChestCollisionList.emplace_back(intersectsSide.first,
																std::move(chest));

							person->block_side(intersectsSide.first, true);
							view->block_side(intersectsSide.first, true);
						}
					}
				}
			}

//END CHECK PERSON INTERACTIOIN WITH CHEST

			loopContainerSize = npcDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
                auto&& npc = npcDispatcher.object(loopContainerIter);

				if(!physics.check_intersection(view.get(), npc.get()))
				{
					npc->visible(false);
				}
				else
				{
					npc->visible(true);
				}

				if(npc->is_visible())
				{

//CHECK NPC INTERACTIOIN WITH MAP OBJECT

					npc->unblock_all_side();

					loopCollisionObjectList = collision.check_object_collision(currentLayout.get(), npc.get());

					if(!loopCollisionObjectList.empty())
					{
						for(auto&& var : loopCollisionObjectList)
						{
							npc->block_side(var.first, true);
						}
					}

//CHECK NPC OBJECT INTERACTIOIN WITH PERSON

					auto&& intersectsSide = collision.check_object_collision(person.get(), npc.get());
					npc->set_state(NPC::State::IDLE);

					person->block_side(intersectsSide.first, true);
					view->block_side(intersectsSide.first, true);

					if (intersectsSide.first != MOVE::Side::NONE )
					{
						npc->set_state(NPC::State::ATTACK);
						npc->block_all_side();

						loopNpcCollisionList.emplace_back(intersectsSide.first, std::move(npc));
					}

//END CHECK PERSON INTERACTIOIN WITH NPC OBJECT

				}
            }
//END CHECK NPC INTERACTIOIN WITH MAP OBJECT


//CHECK PERSON INTERACTIOIN WITH QUEST NPC OBJECT
			//for(const auto& questNpc : questObjectList)
			//{
				//if(const auto& value = collision.check_object_collision(person, questNpc);
						//value.first != MOVE::Side::NONE)
				//{
					//person->block_side(value.first, true);
					//view->block_side(value.first, true);
				//}
			//}
//END CHECK PERSON INTERACTIOIN WITH QUEST NPC OBJECT

			if(personMoveSide != MOVE::Side::NONE)
			{
				mover->move(personMoveSide, person.get(), time / DELAY , SPEED);
				mover->move(personMoveSide, view.get(), time / DELAY , SPEED);

				personLastSide = personMoveSide;
				anim.set_animation(person->get_animation_walk(personMoveSide));
				anim.stop(false);

				person->set_state(NPC::State::WALK);
			}
			else if(person->get_state() == NPC::State::ATTACK)
			{
				anim.set_animation(person->get_animation_attack(personLastSide));
				anim.stop(false);
			}
			else
			{
				if(anim.end())
				{
					anim.reset();
					anim.stop(true);
				}
			}


//DYNAMIC OBJECT ATTACK PERSON, AND UPDATE DYNAMIC OBJECT HEALTH BAR

			if(!loopNpcCollisionList.empty())
			{
				for(auto&& var : loopNpcCollisionList)
				{
					{
						float damageValue = damage.generate(var.second.get(), time * ATTACK_SPEED);

						float health = person->get_health();

						if(damageValue > health)
							person->set_health(0);
						else
							person->set_health(health - damageValue);
					}
                    
					
                    if(var.first == personLastSide)
					{
						if(person->get_state() == NPC::State::ATTACK)
						{
							float damageValue = damage.generate(person.get(), time * ATTACK_SPEED);

							float health = var.second->get_health();

							if(damageValue > health)
								var.second->set_health(0);
							else
								var.second->set_health(health - damageValue);
						}

						float healthBarSize = convert_value(var.second->get_max_health(),
																PROGRESSBARWidth, 
																var.second->get_health());
						if(healthBarSize < 0) healthBarSize = 0;

						enemyHealth->set_size(healthBarSize , PROGRESSBARHeight); 

                        enemyHealthStatus->set_text(std::to_string(var.second->get_health()) + "/"
                                                        + std::to_string(var.second->get_max_health()));

						enemyHealth->visible(true);
                        enemyHealthStatus->visible(true);
					}
				}
			}
			else
			{
                enemyHealthStatus->visible(false);
				enemyHealth->visible(false);
			}

//END

			loopContainerSize = npcDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{

//CHECK LIFE DYNAMIC OBJECT

				auto&& npc = npcDispatcher.object(loopContainerIter);
				if(npc->get_health() <= 0)
				{
					auto&& chest = make_chest(dataBase);
					chest->set_position(npc->get_position());
					for(int a = 0; a < 20; ++a)
					{
						if(a < 10)
						{
							chest->add_elements(create_test_inventory(std::to_string(a),
																	PROGRESSBARHeight / 2, 
																	PROGRESSBARHeight, 
																	BASE::GRAPHIC::Color::Black));
						}
						else
						{
							chest->add_elements(create_test_inventory(std::to_string(a),
																	PROGRESSBARHeight / 2, 
																	PROGRESSBARHeight, 
																	BASE::GRAPHIC::Color::Green));
						}
					}

					chestDispatcher.add_object(std::move(chest));

					npcDispatcher.delete_object(loopContainerIter);
					loopContainerSize = npcDispatcher.size();
					continue;
				}

//END CHECK LIFE DYNAMIC OBJECT


//SET RANDOM NPC MOVE SIDE AND ANIMATION

				if(npc->is_visible())
				{
					randMoveSide = npcDispatcher.side(loopContainerIter, time * DELAY);

					mover->move(randMoveSide, npc.get(), time / DELAY, SPEED);

					auto&& npcAnimation = npcDispatcher.animation(loopContainerIter);

					if(npc->get_state() != NPC::State::ATTACK)
					{
						if(randMoveSide == MOVE::Side::NONE)
						{
							npc->set_state(NPC::State::IDLE);
							npcAnimation.reset();
							npcAnimation.stop(true);
						}
						else
						{
							npc->set_state(NPC::State::WALK);
							npcAnimation.set_animation(npc->get_animation_walk(randMoveSide));
							npcAnimation.stop(false);
						}
					}
					else
					{
						for(auto&& object : loopNpcCollisionList)
						{
							if(object.second == npc)
							{
								npcAnimation.set_animation(npc->get_animation_attack(
														inversion_side(object.first)));
							}
						}

						npcAnimation.stop(false);
					}

//END SET RANDOM NPC MOVE SIDE AND ANIMATION


//DRAW OBJECTS
					app->draw(npcDispatcher.object(loopContainerIter).get());
				}
			}// for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)

//DRAW INVENTORY
//
			if(showInventory)
			{
				if(!loopChestCollisionList.empty())
				{
					loopContainerSize = loopChestCollisionList.size();
					for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
					{
						auto&& intersectsSide = loopChestCollisionList.at(loopContainerIter);
						if(intersectsSide.first == personLastSide)
						{
							auto&& chest = std::move(intersectsSide.second);

							loopRect = view->get_global_bounds();

							loopRectSecond = chestBackground->get_global_bounds();

							chestBackground->set_position((loopRect.left + (loopRect.width * 0.8)) - loopRectSecond.width, 
															loopRect.top + (loopRect.height / 2) * 0.5);

							loopRect = chestBackground->get_global_bounds();
							
							loopRectSecond = arrayNext->get_global_bounds();

							arrayNext->set_position((loopRect.left + (loopRect.width / 2)) + loopRectSecond.width,
													(loopRect.top + loopRect.height) - loopRectSecond.height);


							loopRectSecond = arrayBack->get_global_bounds();

							arrayBack->set_position((loopRect.left + (loopRect.width / 2)) - (loopRectSecond.width * 2),
													(loopRect.top + loopRect.height) - loopRectSecond.height);

							chest->set_page_position(loopRect.left,
														loopRect.top,
														loopRect.width,
														loopRect.height - loopRectSecond.height);
							chest->sort();

							auto collection = chest->get_elements_on_page();

							app->draw(chestBackground.get());
							
							for(auto test : collection)
							{
								if(MOUSE_SINGLE_PRESSED)
								{
									if(physics.check_intersection(test.get(),
												app->map_pixel_to_coords(MOUSE_BUTTON_PRESS_COORDS)))
									{
										std::cout<<test->get_id()<<std::endl;
									}
								}

								app->draw(test.get());
							}
							
							if(MOUSE_SINGLE_PRESSED)
							{
								if(physics.check_intersection(arrayNext.get(),
											app->map_pixel_to_coords(MOUSE_BUTTON_PRESS_COORDS)))
								{
									chest->page_forward();
								}

								if(physics.check_intersection(arrayBack.get(),
											app->map_pixel_to_coords(MOUSE_BUTTON_PRESS_COORDS)))
								{
									chest->page_back();
								}
							}

							app->draw(arrayNext.get());
							app->draw(arrayBack.get());

						}// if((*loopCollisionChestElement).first == personLastSide)
					}// for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
				}//loopChestCollisionList.empty())
				else
				{
					showInventory = false;
				}
			}//if(showInventory)

//END DRAW INVENTORY

			loopContainerSize = chestDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				auto&& chest = chestDispatcher.object(loopContainerIter);
				if(chest->is_visible())
				{
					app->draw(chest.get());
				}
			}
			app->draw(person.get());
            
			app->draw(personHealthBackground.get());
			app->draw(personHealth.get());
			app->draw(personHealthStatus.get());
			
			if(enemyHealth->is_visible())
			{
				app->draw(enemyHealthBackground.get());
				app->draw(enemyHealth.get());
                app->draw(enemyHealthStatus.get());
			}

//END DRAW OBJECTS

			app->display();


//RESET ALL LOOP VARIABLE
			loopCollisionObjectList.clear();
			loopNpcCollisionList.clear();
			loopChestCollisionList.clear();

//END RESET LOOP VARIABLE

		}// while (app->is_open() && isRun)
	}// while(isOpen)

	return EXIT_SUCCESS;
}
