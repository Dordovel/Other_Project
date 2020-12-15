#ifndef SFMLPROJECT_REBUILD_SPRITE_HPP
#define SFMLPROJECT_REBUILD_SPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../struct/database_result.hpp"
#include "./isprite.hpp"

namespace PROJECT::BASE::GRAPHIC
{
    class Sprite : virtual public PROJECT::BASE::GRAPHIC::ISprite
    {
        private:
            sf::Sprite _sprite;
            sf::Texture _texture;
            std::string _id;
            bool _isVisible;
        
            bool _up;
            bool _down;
            bool _left;
            bool _right;


        public:

            explicit Sprite(const PROJECT::DATABASE::DataBaseResult& data);

            ~Sprite();

            Sprite(Sprite&& rectangle) = default;

            Sprite& operator= (Sprite&& rectangle) = default;

            Sprite(const Sprite& rectangle) = default;

            Sprite& operator= (const Sprite& rectangle) = default;

            std::unique_ptr<OBJECT> clone() noexcept override;

            PROJECT::BASE::DATA::DrawableObject draw() const noexcept override;

            void move(PROJECT::BASE::DATA::Vector2F step) noexcept override;

            void move(float X, float Y) noexcept override;

            void set_position(PROJECT::BASE::DATA::Vector2F position) noexcept override;

            void set_position(float X, float Y) noexcept override;

            PROJECT::BASE::DATA::Vector2F get_position() const noexcept override;

            PROJECT::BASE::DATA::RectangleF get_global_bounds() const noexcept override;

            bool collision(const INTERACTION* const object) const noexcept override;
            
            bool collision(PROJECT::BASE::DATA::Vector2F vec) const noexcept override;

            bool collision(PROJECT::BASE::DATA::RectangleF rect) const noexcept override;

            void visible(bool flag) noexcept override;

            bool is_visible() noexcept override;

            void set_scale(PROJECT::BASE::DATA::Vector2F scale) noexcept override;

            PROJECT::BASE::DATA::Vector2F get_scale() noexcept override;

            std::string get_id() const noexcept override;

            void set_id(std::string_view id) noexcept override;

            void block_side(PROJECT::MOVE::Side side, bool status) noexcept override;

            void block_all_side() noexcept override;

            void unblock_all_side() noexcept override;

            void set_texture_rect(PROJECT::BASE::DATA::RectangleI rect) override;
    };
};
#endif //SFMLPROJECT_REBUILD_SPRITE_HPP
