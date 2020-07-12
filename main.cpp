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
#include "./headers/dynamic_obejct_dispatcher.hpp"

using namespace PROJECT;
using namespace std::literals;

float convert_value(int lv, int rv, float value)
{
	return (rv * ((value / lv) * 100)) / 100;
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

std::shared_ptr<NPC::Npc> change_person_type(std::string_view type, const DATABASE::IDataBase& dataBase) noexcept

{
	std::shared_ptr<NPC::Npc> result = nullptr;

	if(type == NPC_JEREMY_PINK)
	{
		result = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_PINK, MOVE::Side::DOWN));
	}

	else if(type == NPC_MARTHA_PINK)
	{
		result = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_PINK, MOVE::Side::DOWN));
	}

	else if(type == NPC_JEREMY_GREEN)
	{
		result = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_GREEN, MOVE::Side::DOWN));
	}

	else if(type == NPC_MARTHA_GREEN)
	{
		result = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_GREEN, MOVE::Side::DOWN));
	}

	else if(type == NPC_JEREMY_BLONDE)
	{
		result = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_BLONDE, MOVE::Side::DOWN));
	}

	else if(type == NPC_MARTHA_BLONDE)
	{
		result = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_BLONDE, MOVE::Side::DOWN));
	}

	return result;
}	

enum class MenuType
{
	MAIN,
	PAUSE
};


std::string menu(MenuType type,
				const std::shared_ptr<APPLICATION::IApplication>& app,
				const std::shared_ptr<APPLICATION::IView>& view) noexcept
{	
	std::shared_ptr<BASE::GRAPHIC::Circle> menuSelectedPointer = std::make_shared<BASE::GRAPHIC::Circle>(8);
	menuSelectedPointer->visible(true);
	menuSelectedPointer->set_points_count(4);
	
	std::pair menu_bg = MAP_PATH.at("menu");

	std::string result;

	std::shared_ptr<COLLECTION::Layout> layout = std::make_shared<COLLECTION::Layout>(menu_bg.first, menu_bg.second);

	if(type == MenuType::MAIN)
	{
		BASE::DATA::Vector2UI layoutSize = layout->get_size();
		view->set_position((layoutSize.x / 2), (layoutSize.y / 2));
		view->set_size(layoutSize.x, layoutSize.y);

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
		BASE::DATA::Vector2UI layoutSize = layout->get_size();
		view->set_position((layoutSize.x / 2), (layoutSize.y / 2));
		view->set_size(layoutSize.x, layoutSize.y);

		result = menu_builder(app, menuSelectedPointer, layout, open_pause_menu());
	}

	return result;
}

int main()
{
    std::shared_ptr<APPLICATION::View> view = std::make_shared<APPLICATION::View>();

    std::shared_ptr<APPLICATION::Application> app = std::make_shared<APPLICATION::Application>("Test_Game", 700, 500);
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
		// std::string result = menu(MenuType::MAIN, app, view);
		// if(result == MENU_EXIT_ITEM || result == EXIT)
		// {
		// 	app->close();
		// 	break;
		// }

		std::shared_ptr<NPC::Npc> person = nullptr;
		// person = change_person_type(result, dataBase);
		person = std::make_shared<NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_PINK, MOVE::Side::DOWN));
		person->set_position(1200, 1200);
		person->set_scale(OBJECT_SCALE);
		person->set_max_health(200);
		person->set_health(person->get_max_health());
		person->set_damage(100);

		std::shared_ptr<NPC::Npc> personTest = nullptr;
		personTest = change_person_type(NPC_JEREMY_GREEN, dataBase);
		personTest->set_position(1230, 1200);
		personTest->set_scale(OBJECT_SCALE);
		personTest->set_max_health(200);
		personTest->set_health(personTest->get_max_health());
		personTest->set_damage(10);
		personTest->set_id("TEST");

		std::shared_ptr<NPC::Npc> personTest1 = nullptr;
		personTest1 = change_person_type(NPC_MARTHA_GREEN, dataBase);
		personTest1->set_position(1170, 1200);
		personTest1->set_scale(OBJECT_SCALE);
		personTest1->set_max_health(200);
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


		anim.set_object(person);

		view->set_position(person->get_position());
		view->set_size(DEFAULT_VIEW_SIZE);
		view->zoom(DEFAULT_VIEW_ZOOM);

		MOVE::Side personMoveSide = MOVE::Side::NONE;
		MOVE::Side randMoveSide = MOVE::Side::DOWN;

		std::pair forest = MAP_PATH.at("forest");
		std::shared_ptr<COLLECTION::Layout> mapForest = std::make_shared<COLLECTION::Layout>(forest.first, forest.second);

		MOVE::Move* mover = new MOVE::Move;

		UNIT::CONTROL::KEYBOARD::KeyboardUnit keyboard;
		UNIT::CONTROL::MOUSE::MouseUnit mouse;

		COLLISION::Collision collision(std::make_shared<BASE::GRAPHIC::Circle>(4));

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

		std::shared_ptr<BASE::GRAPHIC::IRectangle> personHealth;
		personHealth = std::make_shared<BASE::GRAPHIC::Rectangle>(PROGRESSBARWidth, PROGRESSBARHeight);
		personHealth->set_color(BASE::GRAPHIC::Color::Red);
		std::shared_ptr<BASE::GRAPHIC::Text> personHealthStatus = std::make_shared<BASE::GRAPHIC::Text>(RESOURCES_PATH + "Font.otf");
		personHealthStatus->visible(false);
		personHealthStatus->set_font_size(15);
		personHealthStatus->set_color(BASE::GRAPHIC::Color::Black);

		std::shared_ptr<BASE::GRAPHIC::Sprite> personHealthBackground;
		personHealthBackground = std::make_shared<BASE::GRAPHIC::Sprite>(dataBase.get_resources("healthPanel.png", {0, 0, 450, 150}));
		personHealthBackground->set_scale(SPRITEScale);


		std::shared_ptr<BASE::GRAPHIC::IRectangle> enemyHealth;
		enemyHealth	= std::make_shared<BASE::GRAPHIC::Rectangle>(PROGRESSBARWidth, PROGRESSBARHeight);
		enemyHealth->set_color(BASE::GRAPHIC::Color::Purple);
		enemyHealth->visible(false);

		std::shared_ptr<BASE::GRAPHIC::Text> enemyHealthStatus = std::make_shared<BASE::GRAPHIC::Text>(RESOURCES_PATH + "Font.otf");
		enemyHealthStatus->visible(false);
		enemyHealthStatus->set_font_size(15);
		enemyHealthStatus->set_color(BASE::GRAPHIC::Color::Black);

		std::shared_ptr<BASE::GRAPHIC::Sprite> enemyHealthBackground;
		enemyHealthBackground = std::make_shared<BASE::GRAPHIC::Sprite>(dataBase.get_resources("healthPanel.png", {0, 0, 450, 150}));

		enemyHealthBackground->set_scale(SPRITEScale);


		float time;
		auto* currentLayout = &mapForest;
		NPC::DamageGenerator damage;
		damage.set_frame_time(5.F);


//VARIABLE FOR USE IN LOOP
//{
		BASE::DATA::RectangleF loopRect = {};
		BASE::DATA::Vector2F loopVec = {};
		size_t loopContainerIter = 0;
		size_t loopContainerSize = 0;
		std::shared_ptr<NPC::Npc>* loopDynamicElement = nullptr;
		std::shared_ptr<NPC::Npc>* loopDynamicElementCollision = nullptr;
		std::shared_ptr<BASE::GRAPHIC::IText>* loopTextElement = nullptr;
        std::pair interactionDynamicObjectSide = {MOVE::Side::NONE, ""s};
		ANIMATION::Anim* loopDynamicElementAnimation = nullptr;
		std::array<std::pair<MOVE::Side, std::string>, 4> loopCollisionObjectList = {};
        std::pair<MOVE::Side, std::string>* loopCollisionElement = nullptr;
		std::vector<std::pair<MOVE::Side, decltype(loopDynamicElement)>> loopDynamicCollisionList;
		MOVE::Side personLastSide = MOVE::Side::NONE;
//}
//END VARIABLE FOR USE IN LOOP

//VISUAL OBJECT
//{

        DISPATCHER::DynamicObjectDispatcher dynamicObjectDispatcher;
        dynamicObjectDispatcher.add_object(std::move(personTest));
        dynamicObjectDispatcher.add_object(std::move(personTest1));

        std::vector<std::shared_ptr<NPC::QuestNpc>> questObjectList;
        questObjectList.reserve(1);
//}
//END VISUAL OBJECT

		while (app->is_open() && isRun)
		{

//RESET ALL LOOP VARIABLE
			
			interactionDynamicObjectSide = {MOVE::Side::NONE, ""s};
			loopRect = {};
			loopVec = {};
			loopContainerIter = 0;
			loopContainerSize = 0;
			loopDynamicElement = nullptr;
			loopDynamicElementCollision = nullptr;
			loopTextElement = nullptr;
			loopDynamicElementAnimation = nullptr;
			loopCollisionObjectList = {};
			loopCollisionElement = nullptr;
			loopDynamicCollisionList.clear();


			person->unblock_all_side();
			person->set_state(NPC::State::IDLE);
			view->unblock_all_side();

			loopContainerSize = dynamicObjectDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				loopDynamicElement = &dynamicObjectDispatcher.object(loopContainerIter);
				if((*loopDynamicElement)->get_health() <= 0)
				{
					dynamicObjectDispatcher.delete_object(loopContainerIter);
					loopContainerSize = dynamicObjectDispatcher.size();
				}
				else
				{
					(*loopDynamicElement)->set_state(NPC::State::IDLE);
				}
			}

//END RESET LOOP VARIABLE

//EVENT HANDLER
//{
			while (app->check_events())
			{
			    keyboard.catch_events(app->event_handler());
				mouse.catch_events(app->event_handler());
			}
			keyboard.catch_events();
//}
//END EVENT HANDLER

			clock.restart();
			time = clock.get_work_time();

//RUN ANIMATION
			anim.run(time * DELAY);

			loopContainerSize = dynamicObjectDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				dynamicObjectDispatcher.animation(loopContainerIter).run(time * DELAY);
			}
//END RUN ANIMATION

//CHECK LIFE NPC OBJECT

			auto var = app->map_pixel_to_coords(mouse.get_position_in_desktop());
			if(personHealthBackground->collision(var))
			{
				personHealthStatus->visible(true);
			}
			else
			{
				personHealthStatus->visible(false);
			}

//END CHECK LIFE NPC OBJECT



//POSITIONING HEALTH BAR AND UPDATE VALUE
//{
			loopRect = view->get_global_bounds();
			personHealth->set_position((loopRect.left + PROGRESSBARHeight),
										((loopRect.top + loopRect.height) - (PROGRESSBARHeight * 2)));
			personHealth->set_size(convert_value(person->get_max_health(),
													PROGRESSBARWidth,
													person->get_health()), 
									PROGRESSBARHeight); 
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
            
//}
//END POSITIONING HEALTH BAR


//CHECK PERSON INTERACTIOIN WITH MAP OBJECT
//{
            loopCollisionObjectList = collision.check_object_collision(*currentLayout, person);
            loopContainerSize = loopCollisionObjectList.size();
            for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
            {
                loopCollisionElement = &loopCollisionObjectList.at(loopContainerIter);
				person->block_side(loopCollisionElement->first, true);
				view->block_side(loopCollisionElement->first, true);
			}
//}
//END CHECK PERSON INTERACTIOIN WITH MAP OBJECT

//CHECK NPC INTERACTIOIN WITH MAP OBJECT
//{
			loopContainerSize = dynamicObjectDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
                loopDynamicElement = &dynamicObjectDispatcher.object(loopContainerIter);
                ( *loopDynamicElement )->unblock_all_side();

                loopCollisionObjectList = collision.check_object_collision(*currentLayout, ( *loopDynamicElement ));

				for(auto&& var : loopCollisionObjectList)
                {
                    ( *loopDynamicElement )->block_side(var.first, true);
                }

                //CHECK NPC OBJECT INTERACTIOIN WITH PERSON
                //{
                loopCollisionObjectList = collision.check_object_collision(person, ( *loopDynamicElement ));

				for(auto&& var : loopCollisionObjectList)
                {
					person->block_side(var.first, true);
					view->block_side(var.first, true);

                    if ( var.first != MOVE::Side::NONE )
                    {
						(*loopDynamicElement)->set_state(NPC::State::ATTACK);
						(*loopDynamicElement)->block_all_side();

                        loopDynamicCollisionList.emplace_back(var.first, loopDynamicElement);
                    }
                }
                //}
                //END CHECK PERSON INTERACTIOIN WITH NPC OBJECT
            }
//}
//END CHECK NPC INTERACTIOIN WITH MAP OBJECT


//CHECK PERSON INTERACTIOIN WITH QUEST NPC OBJECT
//{
			//for(const auto& questNpc : questObjectList)
			//{
				//if(const auto& value = collision.check_object_collision(person, questNpc);
						//value.first != MOVE::Side::NONE)
				//{
					//person->block_side(value.first, true);
					//view->block_side(value.first, true);
				//}
			//}
//}
//END CHECK PERSON INTERACTIOIN WITH QUEST NPC OBJECT

			if(personMoveSide != MOVE::Side::NONE)
			{
				mover->move(personMoveSide, person, time / DELAY , SPEED);
				mover->move(personMoveSide, view, time / DELAY , SPEED);

				personLastSide = personMoveSide;
				anim.set_animation(&person->get_animation_walk(personMoveSide));
				anim.stop(false);

				person->set_state(NPC::State::WALK);
			}

			if(person->get_state() == NPC::State::ATTACK)
			{
				anim.set_animation(&person->get_animation_attack(personLastSide));
				anim.stop(false);
			}

			if(person->get_state() == NPC::State::IDLE)
			{
				if(anim.end())
				{
					anim.reset();
					anim.stop(true);
				}
			}


//IF PERSON INTERSECTS DYNAMIC OBJECT, LOOPDYNAMICELEMENTCOLLISION != NULLPTR
//DYNAMIC OBJECT ATTACK PERSON, AND UPDATE DYNAMIC OBJECT HEALTH BAR
//{
			if(!loopDynamicCollisionList.empty())
			{
				for(auto&& var : loopDynamicCollisionList)
				{
					auto d = damage.generate((*var.second),
										person,
										time * ATTACK_SPEED);
                    
                    if(d != -1)
                        std::cout<<"DAMAGE: "<<(*var.second)->get_id()<<"->"<<d<<"\n";
					
                    if(var.first == personLastSide)
					{
						if(person->get_state() == NPC::State::ATTACK)
						{
							auto t = damage.generate(person,
											(*var.second),
											time * ATTACK_SPEED);
							std::cout<<"DAMAGE: "<<t<<"\n";
						}

						enemyHealth->set_size(convert_value((*var.second)->get_max_health(),
															PROGRESSBARWidth, 
														(*var.second)->get_health()), 
												PROGRESSBARHeight); 
                        enemyHealthStatus->set_text(std::to_string((*var.second)->get_health()) + "/"
                                                        + std::to_string((*var.second)->get_max_health()));

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
//}
//END
			
//SET RANDOM NPC MOVE SIDE AND ANIMATION
//{
			loopContainerSize = dynamicObjectDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				loopDynamicElement = &dynamicObjectDispatcher.object(loopContainerIter);

				randMoveSide = dynamicObjectDispatcher.side(loopContainerIter, time * DELAY);

				mover->move(randMoveSide, *loopDynamicElement, time / DELAY, SPEED);

				loopDynamicElementAnimation = &dynamicObjectDispatcher.animation(loopContainerIter);

				if((*loopDynamicElement)->get_state() != NPC::State::ATTACK)
				{
					if(randMoveSide == MOVE::Side::NONE)
					{
						(*loopDynamicElement)->set_state(NPC::State::IDLE);
						loopDynamicElementAnimation->reset();
						loopDynamicElementAnimation->stop(true);
					}
					else
					{
						(*loopDynamicElement)->set_state(NPC::State::WALK);
						loopDynamicElementAnimation->set_animation(&(*loopDynamicElement)->get_animation_walk(randMoveSide));
						loopDynamicElementAnimation->stop(false);
					}
				}
				else
				{
					for(auto&& object : loopDynamicCollisionList)
					{
						if(object.second == loopDynamicElement)
						{
							loopDynamicElementAnimation->set_animation(&(*loopDynamicElement)->get_animation_attack(
													inversion_side(object.first)));
						}
					}

					loopDynamicElementAnimation->stop(false);
				}
			}
//}
//END SET RANDOM NPC MOVE SIDE AND ANIMATION

//DRAW OBJECTS
//{
			app->draw(*currentLayout);


			loopContainerSize = dynamicObjectDispatcher.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				app->draw(dynamicObjectDispatcher.object(loopContainerIter));
			}

			app->draw(person);
            app->draw(collision._circleDown);
            app->draw(collision._circleLeft);
            app->draw(collision._circleRight);
            app->draw(collision._circleUp);
            
			app->draw(personHealthBackground);
			app->draw(personHealth);
			if( personHealthStatus->is_visible())
				app->draw(personHealthStatus);
			
			if(enemyHealth->is_visible())
			{
				app->draw(enemyHealthBackground);
				app->draw(enemyHealth);
                app->draw(enemyHealthStatus);
			}
//}
//END DRAW OBJECTS

			app->display();

		}
		delete mover;
	}

	return EXIT_SUCCESS;
}
