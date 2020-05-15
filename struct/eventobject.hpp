#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class EventObject : public sf::Event {};

class Keyboard_Key : public sf::Keyboard {};

class Mouse_Key : public sf::Mouse{};