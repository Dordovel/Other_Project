#ifndef SFMLPROJECT_REBUILD_TEXT_HPP
#define SFMLPROJECT_REBUILD_TEXT_HPP

#include <SFML/Graphics/Text.hpp>
#include "./itext.hpp"

namespace PROJECT::BASE::GRAPHIC
{
    class Text final : public PROJECT::BASE::GRAPHIC::IText
    {
        private:
            std::shared_ptr<sf::Text> _text;
            std::string _id;
            bool _isVisible;
            sf::Font _font;

            bool _up;
            bool _down;
            bool _left;
            bool _right;

        public:

            explicit Text(std::string_view pathToFontFile);

            Text(Text&& rectangle) = default;

            Text& operator= (Text&& rectangle) = default;

            Text(const Text& rectangle) = default;

            Text& operator= (const Text& rectangle) = default;

            ~Text();

			std::shared_ptr<OBJECT> clone() noexcept override;

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

            void set_text(std::string_view str) override;

            void set_font_size(int size) override;

            void set_color(Color color) override;

            void visible(bool flag) noexcept override;

            bool is_visible() noexcept override;

            void set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept override;

            PROJECT::BASE::DATA::Vector2F get_scale() noexcept override;

            void block_side(PROJECT::MOVE::Side side, bool status) noexcept override;

            void block_all_side() noexcept override;

            void unblock_all_side() noexcept override;
    };
};
#endif //SFMLPROJECT_REBUILD_TEXT_HPP
