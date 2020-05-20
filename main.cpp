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
#include "./menu_builder.hpp"


std::string open_type_menu(const std::shared_ptr<ICore>& core, 
													const std::shared_ptr<IView>& view,
													const std::shared_ptr<OBJECT>& menuSelectedPointer)
{
	std::pair menu_bg = MAP_PATH.at("menu");

	std::shared_ptr<ILayout> firstLayout = std::make_shared<Layout>(menu_bg.first, menu_bg.second);
	firstLayout->set_id(NPC_SELECT_TYPT_MENU);

	std::string result;
	std::vector<std::pair<std::string, std::string>> generateItemFirst;

	generateItemFirst.clear();
	generateItemFirst.emplace_back(NPC_BLUE_TYPE_ITEM, "Blue");
	generateItemFirst.emplace_back(NPC_RED_TYPE_ITEM, "Red");
	generateItemFirst.emplace_back(MENU_BACK_ITEM, "Back");

	std::shared_ptr<ILayout> secondLayout = nullptr;
	decltype(generateItemFirst) generateItemSecond;

	while(true)
	{
		result = menu_builder(core, view, menuSelectedPointer, firstLayout, generateItemFirst);

		if(result == NPC_RED_TYPE_ITEM || result == NPC_BLUE_TYPE_ITEM)
		{
			generateItemSecond.clear();

			if(result == NPC_RED_TYPE_ITEM)
			{
				generateItemSecond.emplace_back(NPC_RED_PALADIN, "Paladin");
				generateItemSecond.emplace_back(NPC_RED_MAGIC, "Magic");
				generateItemSecond.emplace_back(NPC_RED_BERSERK, "Berserk");
				generateItemSecond.emplace_back(NPC_RED_WARRIOR, "Warrior");
			}
			else 
			{
				generateItemSecond.emplace_back(NPC_BLUE_PALADIN, "Paladin");
				generateItemSecond.emplace_back(NPC_BLUE_MAGIC, "Magic");
				generateItemSecond.emplace_back(NPC_BLUE_BERSERK, "Berserk");
				generateItemSecond.emplace_back(NPC_BLUE_WARRIOR, "Warrior");
			}

			generateItemSecond.emplace_back(MENU_BACK_ITEM, "Back");

			if(!secondLayout)
			{
				secondLayout = std::make_shared<Layout>(menu_bg.first, menu_bg.second);
				secondLayout->set_id(NPC_SELECT_MENU);
			}
			result = menu_builder(core, view, menuSelectedPointer, secondLayout, generateItemSecond);

			if(result == MENU_BACK_ITEM) continue;
		}
		else if(result == MENU_BACK_ITEM) break;
	}

	return result;

}

std::string open_main_menu(const std::shared_ptr<ICore>& core, 
													const std::shared_ptr<IView>& view,
													const std::shared_ptr<OBJECT>& menuSelectedPointer)
{
	std::pair menu_bg = MAP_PATH.at("menu");
	std::shared_ptr<ILayout> layout = std::make_shared<Layout>(menu_bg.first, menu_bg.second);
	layout->set_id(MAIN_MENU);

	std::vector<std::pair<std::string, std::string>> generateItem;
	generateItem.emplace_back(MAIN_MENU_START_ITEM, "New");
	generateItem.emplace_back(MENU_EXIT_ITEM, "Exit");

	std::string result;

	while (true)
	{
		result = menu_builder(core, view, menuSelectedPointer, layout, generateItem);

		if(result == MENU_EXIT_ITEM)
		{
			core->close();
			break;
		}
		else if(result == MAIN_MENU_START_ITEM)
		{
			result = open_type_menu(core, view, menuSelectedPointer);

			if (result != MENU_BACK_ITEM) break;
		}
	}

	return result;
}


int main()
{
    std::shared_ptr<ICore> core (new Core);

    std::shared_ptr<ILayoutDispatcher> layoutDispatcher (new LayoutDispatcher);

	std::shared_ptr<IEventDispatcher> eventsDispatcher (new EventDispatcher);

    std::unique_ptr<IDataBase> dataBase (new DataBase(RESOURCES_PATH));

    std::shared_ptr<IView> view (new View(DEFAULT_VIEW_SIZE));
    view->zoom(DEFAULT_VIEW_ZOOM);

    std::shared_ptr<IApplication> window (new Application("Test_Game", 700, 500));
    window->init();
    window->set_position(500, 500);
    window->set_view(view);	

	
	std::shared_ptr<Circle> menuSelectedPointer (new Circle(30));
	menuSelectedPointer->set_id(MENU_SELECTED_POINTER);
	menuSelectedPointer->set_scale(CIRCLE_SCALE);
	menuSelectedPointer->visible(true);

    core->register_app(std::move(window));

	std::string result = open_main_menu(core, view, menuSelectedPointer);

	std::cout<<"Type: "<<result<<std::endl;

	return 0;
}
