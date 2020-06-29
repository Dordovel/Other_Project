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
#include "./graphicobject/text.hpp"
#include "./struct/side.hpp"
#include "./menu_builder.hpp"
#include "./id.hpp"
#include "./headers/animation.hpp"
#include "./graphicobject/rectangle.hpp"
#include "./headers/collision.hpp"
#include "./headers/npc.hpp"
#include "./headers/questnpc.hpp"
#include "./headers/attack.hpp"

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

std::shared_ptr<PROJECT::NPC::Npc> change_person_type(std::string_view type, const DATABASE::IDataBase& dataBase, std::string_view id) noexcept

{
	std::shared_ptr<PROJECT::NPC::Npc> result = nullptr;

	if(type == NPC_JEREMY_PINK)
	{
		result = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_PINK, MOVE::Side::DOWN), id);
	}

	else if(type == NPC_MARTHA_PINK)
	{
		result = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_PINK, MOVE::Side::DOWN), id);
	}

	else if(type == NPC_JEREMY_GREEN)
	{
		result = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_GREEN, MOVE::Side::DOWN), id);
	}

	else if(type == NPC_MARTHA_GREEN)
	{
		result = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_GREEN, MOVE::Side::DOWN), id);
	}

	else if(type == NPC_JEREMY_BLONDE)
	{
		result = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_BLONDE, MOVE::Side::DOWN), id);
	}

	else if(type == NPC_MARTHA_BLONDE)
	{
		result = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::MARTHA_BLONDE, MOVE::Side::DOWN), id);
	}

	return result;
}	

enum class MenuType
{
	MAIN,
	PAUSE
};


std::string menu(MenuType type, const std::shared_ptr<APPLICATION::IApplication>& app, const std::shared_ptr<APPLICATION::IView>& view) noexcept
{	
	std::shared_ptr<BASE::GRAPHIC::Circle> menuSelectedPointer = std::make_shared<BASE::GRAPHIC::Circle>(8, MENU_SELECTED_POINTER);
	menuSelectedPointer->visible(true);
	menuSelectedPointer->set_points_count(4);
	
	std::pair menu_bg = MAP_PATH.at("menu");

	std::string result;

	if(type == MenuType::MAIN)
	{
		std::shared_ptr<COLLECTION::Layout> layout = std::make_shared<COLLECTION::Layout>(menu_bg.first, menu_bg.second, MAIN_MENU);

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
		std::shared_ptr<COLLECTION::Layout> layout = std::make_shared<COLLECTION::Layout>(menu_bg.first, menu_bg.second, PAUSE_MENU);

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

	ANIMATION::Anim anim(0.2F);

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

		std::shared_ptr<PROJECT::NPC::Npc> person = nullptr;
		//person = change_person_type(result, dataBase, MAIN_PERSON);
		person = std::make_shared<PROJECT::NPC::Npc>(dataBase.get_resources(DATABASE::PersonProfession::JEREMY_PINK, MOVE::Side::DOWN), MAIN_PERSON);
		person->set_position(1300, 1300);
		person->set_scale(OBJECT_SCALE);
		person->set_max_health(200);
		person->set_health(person->get_max_health());
		person->set_damage(10);

		std::shared_ptr<PROJECT::NPC::Npc> personTest = nullptr;
		personTest = change_person_type(NPC_MARTHA_GREEN, dataBase, "TEST");
		personTest->set_position(1400, 1400);
		personTest->set_scale(OBJECT_SCALE);
		personTest->set_max_health(200);
		personTest->set_health(personTest->get_max_health());
		personTest->set_damage(10);



		std::shared_ptr<PROJECT::NPC::Npc> personTest1 = nullptr;
		personTest1 = change_person_type(NPC_MARTHA_GREEN, dataBase, "TEST");
		personTest1->set_position(1300, 1300);
		personTest1->set_scale(OBJECT_SCALE);
		personTest1->set_max_health(200);
		personTest1->set_health(personTest1->get_max_health());
		personTest1->set_damage(10);

		person->add_animation_walk(MOVE::Side::RIGHT, dataBase.get_animation_walk(MOVE::Side::RIGHT));
		person->add_animation_walk(MOVE::Side::LEFT, dataBase.get_animation_walk(MOVE::Side::LEFT));
		person->add_animation_walk(MOVE::Side::DOWN, dataBase.get_animation_walk(MOVE::Side::DOWN));
		person->add_animation_walk(MOVE::Side::UP, dataBase.get_animation_walk(MOVE::Side::UP));

		
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
		MOVE::Side personLastMoveSide = MOVE::Side::DOWN;
		bool personAttackStatus = false;

		std::pair forest = MAP_PATH.at("forest");
		std::shared_ptr<COLLECTION::Layout> mapForest = std::make_shared<COLLECTION::Layout>(forest.first, forest.second, TOWER_MAP);

		MOVE::Move* mover = new MOVE::Move;

		std::shared_ptr<EVENT::Events> events = std::make_shared<EVENT::Events>(EVENT_MAP);

		COLLISION::Collision collision;

		events->set_close_window_event([&app, &isRun, &isOpen]()
				{
					app->window_close();
					isRun = false;
					isOpen = false;
				});

		events->key_pressed_event(EVENT::Keyboard_Key::Escape, [&app,
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
				}, EVENT::EventHandlerType::EVENT_LOOP);

		events->key_pressed_event(EVENT::Keyboard_Key::E, [&personAttackStatus]()
				{
					personAttackStatus = true;
				}, EVENT::EventHandlerType::NONE);

		events->key_released_event(EVENT::Keyboard_Key::E, [&personAttackStatus]()
				{
					personAttackStatus = false;
				});



		events->key_pressed_event(EVENT::Keyboard_Key::D, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::RIGHT;
				}, EVENT::EventHandlerType::NONE);

		events->key_pressed_event(EVENT::Keyboard_Key::A, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::LEFT;
				}, EVENT::EventHandlerType::NONE);


		events->key_pressed_event(EVENT::Keyboard_Key::S, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::DOWN;
				}, EVENT::EventHandlerType::NONE);


		events->key_pressed_event(EVENT::Keyboard_Key::W, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::UP;
				}, EVENT::EventHandlerType::NONE);


		events->key_pressed_event(EVENT::Keyboard_Key::Right, [&personMoveSide]() 
				{
					personMoveSide = MOVE::Side::RIGHT;
				}, EVENT::EventHandlerType::NONE);


		events->key_pressed_event(EVENT::Keyboard_Key::Left, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::LEFT;
				}, EVENT::EventHandlerType::NONE);


		events->key_pressed_event(EVENT::Keyboard_Key::Down, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::DOWN;
				}, EVENT::EventHandlerType::NONE);


		events->key_pressed_event(EVENT::Keyboard_Key::Up, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::UP;
				}, EVENT::EventHandlerType::NONE);


		events->key_released_event(EVENT::Keyboard_Key::D, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::A, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::S, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::W, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::Right, [&personMoveSide]() 
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::Left, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::Down, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});

		events->key_released_event(EVENT::Keyboard_Key::Up, [&personMoveSide]()
				{
					personMoveSide = MOVE::Side::NONE;
				});


		const int PROGRESSBARWidth = 115;
		const int PROGRESSBARHeight = 25;
		const BASE::DATA::Vector2F SPRITEScale = {0.3, 0.3};

		std::shared_ptr<BASE::GRAPHIC::IRectangle> personHealth;
		personHealth = std::make_shared<BASE::GRAPHIC::Rectangle>(PROGRESSBARWidth, PROGRESSBARHeight, "HEALTH");
		personHealth->set_color(BASE::GRAPHIC::Color::Red);

		std::shared_ptr<BASE::GRAPHIC::Sprite> personHealthBackground;
		personHealthBackground = std::make_shared<BASE::GRAPHIC::Sprite>(dataBase.get_resources("healthPanel.png", {0, 0, 450, 150}),
																			"ENEMY_HEALTHBackground");

		personHealthBackground->set_scale(SPRITEScale);


		std::shared_ptr<BASE::GRAPHIC::IRectangle> enemyHealth;
		enemyHealth	= std::make_shared<BASE::GRAPHIC::Rectangle>(PROGRESSBARWidth, PROGRESSBARHeight, "ENEMY_HEALTH");
		enemyHealth->set_color(BASE::GRAPHIC::Color::Purple);
		enemyHealth->visible(false);


		std::shared_ptr<BASE::GRAPHIC::Sprite> enemyHealthBackground;
		enemyHealthBackground = std::make_shared<BASE::GRAPHIC::Sprite>(dataBase.get_resources("healthPanel.png", {0, 0, 450, 150}),
																			"ENEMY_HEALTHBackground");

		enemyHealthBackground->set_scale(SPRITEScale);

		auto text = std::make_shared<BASE::GRAPHIC::Text>(RESOURCES_PATH + "Font.otf", personTest->get_id());
		text->visible(true);
		text->set_color(BASE::GRAPHIC::Color::Black);
		text->set_font_size(20);


		auto text1 = std::make_shared<BASE::GRAPHIC::Text>(RESOURCES_PATH + "Font.otf", personTest1->get_id());
		text->visible(true);
		text->set_color(BASE::GRAPHIC::Color::Black);
		text->set_font_size(20);


		float time;
		auto* currentLayout = &mapForest;
		NPC::Attack attack;
		attack.set_param(5.F);

//VARIABLE FOR USE IN LOOP
//{
		std::pair attackDamage = {-1, -1};
		std::pair interactionStaticObjectSide(MOVE::Side::NONE, ""s);
		std::pair interactionDynamicObjectSide(MOVE::Side::NONE, ""s);
		BASE::DATA::RectangleF loopRect = {};
		BASE::DATA::Vector2F loopVec = {};
		size_t loopContainerIter = 0;
		size_t loopContainerSize = 0;
		std::shared_ptr<NPC::Npc>* loopDynamicElement = nullptr;
		std::shared_ptr<NPC::Npc>* loopDynamicElementCollision = nullptr;
		ANIMATION::Anim* loopDynamicElementAnimation = nullptr;
		std::shared_ptr<BASE::GRAPHIC::IText>* loopTextElement = nullptr;
//}
//END VARIABLE FOR USE IN LOOP

//VISUAL OBJECT
//{
		std::vector<std::shared_ptr<NPC::Npc>> dynamicObjectList;
		dynamicObjectList.reserve(2);
		dynamicObjectList.emplace_back(std::move(personTest));
		dynamicObjectList.emplace_back(std::move(personTest1));

		std::vector<std::shared_ptr<NPC::QuestNpc>> questObjectList;
		questObjectList.reserve(1);

		std::vector<std::shared_ptr<BASE::GRAPHIC::IText>> dynamicElementStatus;
		dynamicElementStatus.reserve(2);
		dynamicElementStatus.emplace_back(std::move(text));
		dynamicElementStatus.emplace_back(std::move(text1));

		std::array<ANIMATION::Anim, 2> dynamicElementAnimation = {0.2F, 0.2F};

		loopContainerSize = dynamicObjectList.size();
		for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
		{
			loopDynamicElementAnimation = &dynamicElementAnimation.at(loopContainerIter);
			loopDynamicElementAnimation->set_object(dynamicObjectList.at(loopContainerIter));
		}

		std::random_device rand_device;
		std::mt19937 mt(rand_device());
		std::uniform_real_distribution<float> uid (0.1F, 1.F);

//}
//END VISUAL OBJECT


		while (app->is_open() && isRun)
		{
//CLEAR ALL LOOP VARIABLE
			
			attackDamage = {-1, -1};
			interactionStaticObjectSide = {MOVE::Side::NONE, ""s};
			interactionDynamicObjectSide = {MOVE::Side::NONE, ""s};
			loopRect = {};
			loopVec = {};
			loopContainerIter = 0;
			loopContainerSize = 0;
			loopDynamicElement = nullptr;
			loopDynamicElementCollision = nullptr;
			loopTextElement = nullptr;

//END CLEAR LOOP VARIABLE


			clock.restart();
			time = clock.get_work_time();

			anim.run(time * DELAY);

			for(auto& value : dynamicElementAnimation)
			{
				value.run(time * DELAY);
			}

//EVENT HANDLER
//{
			while (app->event_handler(events->get_event_object()))
			{
				events->catch_events_loop();
			}
			events->catch_events_none();
//}
//END EVENT HANDLER


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
			personHealthBackground->set_position((loopVec.x - 10),
													(loopVec.y - 10));

			loopRect = view->get_global_bounds();
			enemyHealth->set_position((loopRect.left + (loopRect.width * 0.5) - (PROGRESSBARWidth * 0.5)),
										(loopRect.top + PROGRESSBARHeight));
			loopVec = enemyHealth->get_position();

			enemyHealthBackground->set_position((loopVec.x - 10),
												(loopVec.y - 10));
//}
//END POSITIONING HEALTH BAR

			person->unblock_all_side();
			view->unblock_all_side();

//CHECK PERSON INTERACTIOIN WITH MAP OBJECT
//{
			if(const auto& value = collision.check_object_collision(*currentLayout, person); 
					value.first != MOVE::Side::NONE)
			{
				person->block_side(value.first, true);
				view->block_side(value.first, true);

				interactionStaticObjectSide = value;
			}
//}
//END CHECK PERSON INTERACTIOIN WITH MAP OBJECT

//CHECK NPC INTERACTIOIN WITH MAP OBJECT
//{
			loopContainerSize = dynamicObjectList.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				loopDynamicElement = &dynamicObjectList.at(loopContainerIter);
				(*loopDynamicElement)->unblock_all_side();

				if(const auto& value = collision.check_object_collision(*currentLayout, (*loopDynamicElement)); 
						value.first != MOVE::Side::NONE)
				{
					(*loopDynamicElement)->block_side(value.first, true);
				}	

	//CHECK PERSON INTERACTIOIN WITH NPC OBJECT
	//{
				if(const auto& value = collision.check_object_collision(person, (*loopDynamicElement));
						value.first != MOVE::Side::NONE)
				{
					person->block_side(value.first, true);
					view->block_side(value.first, true);

					loopDynamicElementCollision = loopDynamicElement;
					interactionDynamicObjectSide = value;

					(*loopDynamicElement)->block_all_side();
				}
	//}
	//END CHECK PERSON INTERACTIOIN WITH NPC OBJECT
			}
//}
//END CHECK NPC INTERACTIOIN WITH MAP OBJECT


//CHECK PERSON INTERACTIOIN WITH QUEST NPC OBJECT
//{
			for(const auto& questNpc : questObjectList)
			{
				if(const auto& value = collision.check_object_collision(person, questNpc);
						value.first != MOVE::Side::NONE)
				{
					person->block_side(value.first, true);
					view->block_side(value.first, true);
				}
			}
//}
//END CHECK PERSON INTERACTIOIN WITH QUEST NPC OBJECT

			if(personMoveSide != MOVE::Side::NONE)
			{
				mover->move(personMoveSide, person, time / DELAY , SPEED);
				mover->move(personMoveSide, view, time / DELAY , SPEED);

				personLastMoveSide = personMoveSide;

				anim.set_animation(&person->get_animation_walk(personMoveSide));
				anim.stop(false);
			}

			if(personAttackStatus)
			{
				if(interactionDynamicObjectSide.first != MOVE::Side::NONE)
				{
					anim.set_animation(&person->get_animation_attack(interactionDynamicObjectSide.first));
				}
				else
				{
					anim.set_animation(&person->get_animation_attack(personLastMoveSide));
				}
				anim.stop(false);
			}

			if(personMoveSide == MOVE::Side::NONE
					&& !personAttackStatus)
			{
				if(anim.end())
				{
					anim.stop(true);
				}
			}


//IF PERSON INTERSECTS DYNAMIC OBJECT, LOOPDYNAMICELEMENTCOLLISION != NULLPTR
//DYNAMIC OBJECT ATTACK PERSON, AND UPDATE DYNAMIC OBJECT HEALTH BAR
//{
			if(loopDynamicElementCollision)
			{
				attackDamage = attack.attack(person,
											(*loopDynamicElementCollision),
											personAttackStatus,
											time * DELAY);

				enemyHealth->set_size(convert_value((*loopDynamicElementCollision)->get_max_health(),
													PROGRESSBARWidth, 
													(*loopDynamicElementCollision)->get_health()), 
										PROGRESSBARHeight); 
				enemyHealth->visible(true);
			}
			else
			{
				enemyHealth->visible(false);
			}
//}
//END
	
//DRAW OBJECTS
//{
			app->draw(*currentLayout);
			app->draw(personHealthBackground);
			app->draw(personHealth);
			
			if(enemyHealth->is_visible())
			{
				app->draw(enemyHealthBackground);
				app->draw(enemyHealth);
			}


			loopContainerSize = dynamicObjectList.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				loopDynamicElement = &dynamicObjectList.at(loopContainerIter);

				mover->move(MOVE::Side::DOWN, *loopDynamicElement, time / DELAY, uid(mt));

				loopDynamicElementAnimation = &dynamicElementAnimation.at(loopContainerIter);

				if(interactionDynamicObjectSide.first == MOVE::Side::NONE)
				{
					loopDynamicElementAnimation->set_animation(&(*loopDynamicElement)->get_animation_walk(MOVE::Side::DOWN));
				}
				else
				{
					loopDynamicElementAnimation->set_animation(&(*loopDynamicElement)->get_animation_attack(
											inversion_side(interactionDynamicObjectSide.first)));
				}

				loopDynamicElementAnimation->stop(false);
			}


			loopContainerSize = dynamicObjectList.size();
			for(loopContainerIter = 0; loopContainerIter < loopContainerSize; ++loopContainerIter)
			{
				loopDynamicElement = &dynamicObjectList.at(loopContainerIter);
				app->draw(*loopDynamicElement);

				loopTextElement = &dynamicElementStatus.at(loopContainerIter);
				loopRect = (*loopTextElement)->get_global_bounds();
				loopVec = {15, loopRect.height * 2};

				(*loopTextElement)->set_position((*loopDynamicElement)->get_position() - loopVec);
				(*loopTextElement)->set_text(std::to_string((*loopDynamicElement)->get_health()) + "/" + std::to_string((*loopDynamicElement)->get_max_health()));

				app->draw(*loopTextElement);
			}

			app->draw(person);
//}
//END DRAW OBJECTS

			app->display();

		}

		delete mover;
	}

	return EXIT_SUCCESS;
}
