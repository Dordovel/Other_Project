#pragma once
#include "./struct/vector_object.hpp"
#include <map>

const PROJECT::BASE::DATA::Vector2F DEFAULT_POSITION = {1200, 1200};
const float ANIMATION_FRAME = 0.2F;
const int SPEED = 2;
const float DELAY = 4.F;
const int ATTACK_SPEED  = 6.F;
const PROJECT::BASE::DATA::Vector2F OBJECT_SCALE = {1, 1.3f};
const PROJECT::BASE::DATA::Vector2F DEFAULT_VIEW_SIZE = {300, 300};
const float DEFAULT_VIEW_ZOOM = 2;
const PROJECT::BASE::DATA::Vector2F CIRCLE_SCALE = {0.2f, 0.2f};
const std::string RESOURCES_PATH = "./Game_Resources/Image/";
const std::map<std::string, std::pair<std::string, std::string>, std::less<>> MAP_PATH = 
  									{
  										{"menu", std::pair("./Game_Resources/Image/", "main_menu.tmx")},
  										{"forest", std::pair("./Game_Resources/Image/forest/", "main.tmx")},
  										{"desert", std::pair("./Game_Resources/Image/desert/", "tower.tmx")}
  									};
