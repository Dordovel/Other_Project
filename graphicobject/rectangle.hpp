#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "./irectangle.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace PROJECT::BASE::GRAPHIC
{
    class Rectangle final : public PROJECT::BASE::GRAPHIC::IRectangle
    {
        private:
            std::shared_ptr<sf::RectangleShape> _rectangle;
            std::string _id;
            bool _isVisible;
			std::shared_ptr<sf::Texture> _texture;

            bool _up, _down, _left, _right;

        public:

			void set_texture(const PROJECT::DATABASE::DataBaseResult& resources) override;

            PROJECT::BASE::DATA::DrawableObject draw() const noexcept override;

            std::string get_id() const noexcept override;

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

            void set_size(const BASE::DATA::Vector2F& size) noexcept override;

            void set_size(float width, float height) noexcept override;

            BASE::DATA::Vector2F get_size() const noexcept override;

            ~Rectangle();

            explicit Rectangle(float width, float height, std::string_view id);

            explicit Rectangle(PROJECT::BASE::DATA::Vector2F size, std::string_view id);

			Rectangle(Rectangle&&) = default;

			Rectangle& operator= (Rectangle&&) = default;
    };
};
