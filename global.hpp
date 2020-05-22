#pragma once
#include "./struct/vectorobject.hpp"
#include <map>

constexpr int SPEED = 2;
const static Vector2F DEFAULT_VIEW_SIZE = {300, 300};
constexpr int DEFAULT_VIEW_ZOOM = 2;
const static std::string NPC_FILE_NAME = "hero.png";
const static Vector2F OBJECT_SCALE = {0.2f, 0.3f};
const static Vector2F CIRCLE_SCALE = {0.2f, 0.2f};
const static std::string RESOURCES_PATH = "./Game_Resources/Image/";
const static std::map<std::string, std::pair<std::string, std::string>, std::less<>> MAP_PATH = 
									{
										{"menu", std::pair("./Game_Resources/Image/", "main_menu.tmx")},
										{"forest", std::pair("./Game_Resources/Image/forest/", "main.tmx")},
										{"desert", std::pair("./Game_Resources/Image/desert/", "tower.tmx")}
									};

