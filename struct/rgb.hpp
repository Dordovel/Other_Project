#pragma once 
#include <SFML/Graphics/Color.hpp>
#include "./color.hpp"

namespace PROJECT::BASE::GRAPHIC
{
    class RGB : public sf::Color 
    {
        public:
            RGB(int red, int green, int blue):sf::Color(red, green, blue){};
			
		 	static RGB color (const PROJECT::BASE::GRAPHIC::Color& color)
			{
				switch(color)
				{
					case PROJECT::BASE::GRAPHIC::Color::White:
						return RGB(255, 255, 255);

					case PROJECT::BASE::GRAPHIC::Color::Black:
						return RGB(0, 0, 0);

					case PROJECT::BASE::GRAPHIC::Color::Cyan:
						return RGB(0, 206, 209);

					case PROJECT::BASE::GRAPHIC::Color::Green:
						return RGB(0, 255, 0);

					case PROJECT::BASE::GRAPHIC::Color::Orange:
						return RGB(255, 140, 0);

					case PROJECT::BASE::GRAPHIC::Color::Red:
						return RGB(255, 0, 0);

					case PROJECT::BASE::GRAPHIC::Color::Purple:
						return RGB(138,43,226);
						
					case PROJECT::BASE::GRAPHIC::Color::Yellow:
						return RGB(255, 255, 0);

					case PROJECT::BASE::GRAPHIC::Color::Blue:
						return RGB(0, 0, 255);
						
				}

				return RGB(0, 0, 0);
			}
    };
};
