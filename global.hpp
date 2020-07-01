#pragma once
#include "./struct/vectorobject.hpp"
#include <map>

inline constexpr float ANIMATION_FRAME = 0.2F;
inline constexpr int SPEED = 2;
inline constexpr float DELAY = 4;
inline const static PROJECT::BASE::DATA::Vector2F OBJECT_SCALE = {1, 1.3f};
inline const static PROJECT::BASE::DATA::Vector2F DEFAULT_VIEW_SIZE = {300, 300};
inline constexpr float DEFAULT_VIEW_ZOOM = 2;
inline const static PROJECT::BASE::DATA::Vector2F CIRCLE_SCALE = {0.2f, 0.2f};
inline const static std::string RESOURCES_PATH = "./Game_Resources/Image/";
inline const static std::map<std::string, std::pair<std::string, std::string>, std::less<>> MAP_PATH = 
 									{
 										{"menu", std::pair("./Game_Resources/Image/", "main_menu.tmx")},
 										{"forest", std::pair("./Game_Resources/Image/forest/", "main.tmx")},
 										{"desert", std::pair("./Game_Resources/Image/desert/", "tower.tmx")}
 									};
 
