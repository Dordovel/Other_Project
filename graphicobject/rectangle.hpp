#pragma once

#include "../struct/colorobject.hpp"
#include "../object/object.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../object/scalable.hpp"

class Rectangle final : public OBJECT, public SCALABLE
{
	private:
		std::shared_ptr<sf::RectangleShape> _rectangle;
		std::string _id;
		bool _isVisible;

		bool _up, _down, _left, _right;		

	public:
				
        DrawableObject draw() const noexcept override;

        void set_id(const std::string& id) noexcept override;

        std::string get_id() const noexcept override;

        void set_position(const Vector2F& position) noexcept override;

        void set_position(float X, float Y) noexcept override;

        void rotate(float angle) noexcept override;

        bool collision(const std::shared_ptr<INTERACTION>& object) noexcept override;

        bool collision(const Vector2F& object) noexcept override;

        void move(const Vector2F& step) noexcept override;

        void move(float X, float Y) noexcept override;

        Vector2F get_position() const noexcept override;

        RectangleF get_global_bounds() const noexcept override;

        explicit Rectangle(float width, float height);

        explicit Rectangle(Vector2F size);

        void visible(bool flag) noexcept override;

        bool is_visible() noexcept override;

		void set_scale(Vector2F scale) noexcept override;

		Vector2F get_scale() noexcept override;

		void block_side(SIDE side, bool status) noexcept override;
		
		void set_color(const Color& color);
};
