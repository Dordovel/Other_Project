#ifndef SFMLPROJECT_REBUILD_STRUCT_EVENT_OBJECT_HPP
#define SFMLPROJECT_REBUILD_STRUCT_EVENT_OBJECT_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace PROJECT::UNIT::CONTROL::KEYBOARD
{
    class Keyboard_Key : public sf::Keyboard {};
};

namespace PROJECT::UNIT::CONTROL::MOUSE
{
    class Mouse_Key : public sf::Mouse{};
};

namespace PROJECT::EVENT
{
    class EventObject : public sf::Event {};
};
#endif //SFMLPROJECT_REBUILD_STRUCT_EVENT_OBJECT_HPP