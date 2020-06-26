#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <ostream>

namespace PROJECT::BASE::DATA
{
    class RectangleI : public sf::Rect<int>
    {
        public:
            RectangleI(int rectLeft, int rectTop, int rectWidth, int rectHeight):
                                                            sf::Rect<int>(rectLeft, rectTop, rectWidth, rectHeight){}
            RectangleI(const sf::Rect<int>& src):sf::Rect<int>(src){}
            RectangleI():sf::Rect<int>(){}

            friend std::ostream& operator<<(std::ostream& os, const RectangleI& rect)
            {
                os <<"RectangleI:\tLeft->"<< rect.left << "\tTop->" << rect.top << "\tHeight->"<< rect.height << "\tWidth->" << rect.width;
                return os;
            }

            friend std::ostream& operator<<(std::ostream& os, const sf::Rect<int>& rect)
            {
                os <<"RectangleI:\tLeft->"<< rect.left << "\tTop->" << rect.top << "\tHeight->"<< rect.height << "\tWidth->" << rect.width;
                return os;
            }
    };

    class RectangleF : public sf::Rect<float>
    {
        public:
            RectangleF(float rectLeft, float rectTop, float rectWidth, float rectHeight):
                    sf::Rect<float>(rectLeft, rectTop, rectWidth, rectHeight){}
            RectangleF(const sf::Rect<float>& src):sf::Rect<float>(src){}
            RectangleF():sf::Rect<float>(){}

            friend std::ostream& operator<<(std::ostream& os, const RectangleF& rect)
            {
                os <<"RectangleF:\tLeft->"<< rect.left << "\tTop->" << rect.top << "\tHeight->"<< rect.height << "\tWidth->" << rect.width;
                return os;
            }

            friend std::ostream& operator<<(std::ostream& os, const sf::Rect<float>& rect)
            {
                os <<"RectangleF:\tLeft->"<< rect.left << "\tTop->" << rect.top << "\tHeight->"<< rect.height << "\tWidth->" << rect.width;
                return os;
            }
    };
};