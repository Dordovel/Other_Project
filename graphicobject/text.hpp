#pragma once

#include "../object/drawable.hpp"
#include "../Interface/iobject.hpp"
#include <SFML/Graphics/Text.hpp>
#include "../struct/colorobject.hpp"
#include "../object/scalable.hpp"

class Text : public IOBJECT, public DRAWABLE, public SCALABLE
{
	private:
        std::shared_ptr<sf::Text> _text;
        std::string _id;
        bool _isVisible;

	public:

        DrawableObject draw() const override;

        void set_id(const std::string& id) override;

        std::string get_id() const override;

        void set_position(const Vector2F& position) override;

        void set_position(float X, float Y) override;

        void rotate(float angle) override;

        bool collision(const std::shared_ptr<INTERACTION>& object) override;

        void move(const Vector2F& step) override;

        void move(float X, float Y) override;

        Vector2F get_position() const override;

        RectangleF get_global_bounds() const override;

        explicit Text(const std::string& pathToFontFile);

		void set_text(const std::string& str);

		void set_font_size(int size);

		void set_color(const Color& color);

        void visible(bool flag) override;

        bool is_visible() override;

		void set_scale(Vector2F scale) override;

		Vector2F get_scale() override;
};
