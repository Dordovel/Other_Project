#ifndef SFMLPROJECT_REBUILD_RECTANGLE_HPP
#define SFMLPROJECT_REBUILD_RECTANGLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include "./irectangle.hpp"

namespace PROJECT::BASE::GRAPHIC
{
    class Rectangle final : public PROJECT::BASE::GRAPHIC::IRectangle
    {
        private:
            sf::RectangleShape _rectangle;
            std::string _id;
            bool _isVisible;

            bool _up, _down, _left, _right;

        public:

            explicit Rectangle(float width, float height);

            explicit Rectangle(PROJECT::BASE::DATA::Vector2F size);

            Rectangle(Rectangle&& rectangle) = default;

            Rectangle& operator= (Rectangle&& rectangle) = default;

            Rectangle(const Rectangle& rectangle) = default;

            Rectangle& operator= (const Rectangle& rectangle) = default;

            ~Rectangle();

			std::unique_ptr<OBJECT> clone() noexcept override;

            PROJECT::BASE::DATA::DrawableObject draw() const noexcept override;

            std::string get_id() const noexcept override;

            void set_id(std::string_view id) noexcept override;

            void set_position(PROJECT::BASE::DATA::Vector2F position) noexcept override;

            void set_position(float X, float Y) noexcept override;

            bool collision(const INTERACTION* const object) const noexcept override;

            bool collision(PROJECT::BASE::DATA::Vector2F vec) const noexcept override;

            bool collision(PROJECT::BASE::DATA::RectangleF rect) const noexcept override;

            void move(PROJECT::BASE::DATA::Vector2F step) noexcept override;

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
            
            void set_color(Color color) override;

            void set_size(BASE::DATA::Vector2F size) noexcept override;

            void set_size(float width, float height) noexcept override;

            BASE::DATA::Vector2F get_size() const noexcept override;
    };
};
#endif // SFMLPROJECT_REBUILD_RECTANGLE_HPP
