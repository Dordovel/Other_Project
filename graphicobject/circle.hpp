#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>
#include "./icircle.hpp"

namespace PROJECT::BASE::GRAPHIC
{
    class Circle final : public PROJECT::BASE::GRAPHIC::ICircle
    {
        private:
            std::shared_ptr<sf::CircleShape> _circleShape;
            std::string _id;
            bool _isVisible;
            bool _up;
            bool _down;
            bool _left;
            bool _right;

        public:
			std::shared_ptr<OBJECT> clone() noexcept override;	

            PROJECT::BASE::DATA::DrawableObject draw() const noexcept override;

            std::string get_id() const noexcept override;

            void set_id(std::string_view id) noexcept override;

            void set_position(const PROJECT::BASE::DATA::Vector2F& position) noexcept override;

            void set_position(float X, float Y) noexcept override;

            bool collision(const std::shared_ptr<INTERACTION>& object) noexcept override;

            bool collision(const PROJECT::BASE::DATA::Vector2F& vec) noexcept override;

            bool collision(const PROJECT::BASE::DATA::RectangleF& rect) noexcept override;

            void move(const PROJECT::BASE::DATA::Vector2F& step) noexcept override;

            void move(float X, float Y) noexcept override;

            PROJECT::BASE::DATA::Vector2F get_position() const noexcept override;

            PROJECT::BASE::DATA::RectangleF get_global_bounds() const noexcept override;

            void visible(bool flag) noexcept override;

            bool is_visible() noexcept override;

            void set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept override;

            PROJECT::BASE::DATA::Vector2F get_scale() noexcept override;

            void block_side(PROJECT::MOVE::Side side, bool status) noexcept override;

            void block_all_side() noexcept override;

            void unblock_all_side() noexcept override;
            
            void set_color(const Color& color) override;

            void set_points_count(int points) override;

            explicit Circle(float radius);

            ~Circle();
    };
};
