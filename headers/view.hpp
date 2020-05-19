#pragma once

#include "../Interface/iview.hpp"
#include <SFML/Graphics/View.hpp>

class View: public IView, public sf::View
{
	private:
		bool _up;
		bool _down;
		bool _left;
		bool _right;

    public:

        View(float X, float Y, float Width, float Height);

        View(const Vector2F& position, float Width, float Height);

        View(const Vector2F& position, const Vector2F& size);

        View(const Vector2F& size);

        void zoom(float zoom) override;

        void set_position(const Vector2F& position) override;

        void set_position(float X, float Y) override;

        void rotate(float angle) override;

        bool collision(const std::shared_ptr<INTERACTION>& object) override;

        bool collision(const Vector2F& object) override;

        void move(const Vector2F& step) override;

        void move(float X, float Y) override;

        Vector2F get_position() const override;

        RectangleF get_global_bounds() const override;

		Vector2F get_size() const override;

		void set_size(const Vector2F& size) override;

		void set_size(float x, float y) override;
	
		void block_side(SIDE side, bool status) override;
	
		~View() = default;
};
