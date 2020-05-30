#pragma once

#include "../Interface/iview.hpp"
#include <SFML/Graphics/View.hpp>

class View final : public IView, public sf::View
{
	private:
		bool _up;
		bool _down;
		bool _left;
		bool _right;

    public:
		
		View() = default;

        View(float X, float Y, float Width, float Height);

        View(const Vector2F& position, float Width, float Height);

        View(const Vector2F& position, const Vector2F& size);

        View(const Vector2F& size);

        void zoom(float zoom) noexcept override;

        void set_position(const Vector2F& position) noexcept override;

        void set_position(float X, float Y) noexcept override;

        void rotate(float angle) noexcept override;

        bool collision(const std::shared_ptr<INTERACTION>& object) noexcept override;

        bool collision(const Vector2F& object) noexcept override;

        void move(const Vector2F& step) noexcept override;

        void move(float X, float Y) noexcept override;

        Vector2F get_position() const noexcept override;

        RectangleF get_global_bounds() const noexcept override;

		Vector2F get_size() const noexcept override;

		void set_size(const Vector2F& size) noexcept override;

		void set_size(float x, float y) noexcept override;
	
		void block_side(SIDE side, bool status) noexcept override;
	
		~View() = default;
};
