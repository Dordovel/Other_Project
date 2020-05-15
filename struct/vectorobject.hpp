#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>

class Vector2I: public sf::Vector2<int>
{
    public:
        Vector2I(int X, int Y):sf::Vector2<int>(X, Y){};
        Vector2I(Vector2I const &src):sf::Vector2<int>(src.x, src.y){};
        Vector2I(sf::Vector2<int> src):sf::Vector2<int>(src){};
        Vector2I():sf::Vector2<int>(){};

        friend std::ostream& operator<<(std::ostream& os, const Vector2I& dt)
        {
            os <<"Vector2I:\tX->"<< dt.x << "\tY->" << dt.y;
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const sf::Vector2<int>& dt)
        {
            os <<"Vector2I:\tX->"<< dt.x << "\tY->" << dt.y;
            return os;
        }
};

class Vector2F: public sf::Vector2<float>
{
    public:
        Vector2F(float X, float Y):sf::Vector2<float>(X, Y){};
        Vector2F(Vector2F const &src):sf::Vector2<float>(src.x, src.y){};
        Vector2F(sf::Vector2<float > src):sf::Vector2<float >(src){};
        Vector2F():sf::Vector2<float>(){};

        friend std::ostream& operator<<(std::ostream& os, const Vector2F& dt)
        {
            os <<"Vector2F:\tX->"<< dt.x << "\tY->" << dt.y;
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const sf::Vector2<float>& dt)
        {
            os <<"Vector2F:\tX->"<< dt.x << "\tY->" << dt.y;
            return os;
        }
};

class Vector2UI: public sf::Vector2<unsigned int>
{
    public:
        Vector2UI(unsigned int X, unsigned int Y):sf::Vector2<unsigned int>(X, Y){};
        Vector2UI(Vector2UI const &src):sf::Vector2<unsigned int>(src.x, src.y){};
        Vector2UI(sf::Vector2<unsigned int> src):sf::Vector2<unsigned int>(src){};
        Vector2UI():sf::Vector2<unsigned int>(){};

        friend std::ostream& operator<<(std::ostream& os, const Vector2UI& dt)
        {
            os <<"Vector2UI:\tX->"<< dt.x << "\tY->" << dt.y;
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const sf::Vector2<unsigned int>& dt)
        {
            os <<"Vector2UI:\tX->"<< dt.x << "\tY->" << dt.y;
            return os;
        }
};