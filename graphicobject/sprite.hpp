#pragma once
#include <map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../struct/databaseresult.hpp"
#include <memory>
#include "../object/scalable.hpp"
#include "../object/object.hpp"
#include "../object/animated.hpp"

class Sprite : public OBJECT, public SCALABLE, public ANIMATED
{
    private:
        std::shared_ptr<sf::Sprite> _sprite;
        std::shared_ptr<sf::Texture> _texture;
        std::string _id;
        bool _isVisible;
	
		bool _up;
		bool _down;
		bool _left;
		bool _right;


    public:
        explicit Sprite(const DataBaseResult& data);

        DrawableObject draw() const noexcept override;

        ~Sprite() override = default;

        void move(const Vector2F& step) noexcept override;

        void move(float X, float Y) noexcept override;

        void set_position(const Vector2F& position) noexcept override;

        void set_position(float X, float Y) noexcept override;

        Vector2F get_position() const noexcept override;

        void rotate(float angle) noexcept override;

        RectangleF get_global_bounds() const noexcept override;

        bool collision(const std::shared_ptr<INTERACTION>& object) noexcept override;
		
        bool collision(const Vector2F& object) noexcept override;

        void set_id(const std::string& name) noexcept override;

        void visible(bool flag) noexcept override;

        bool is_visible() noexcept override;

		void set_scale(Vector2F scale) noexcept override;

		Vector2F get_scale() noexcept override;

        std::string get_id() const noexcept override;

		void block_side(SIDE side, bool status) noexcept override;

		void set_texture(const DataBaseResult& data) override;

		void set_texture_rect(const RectangleI& rect) override;

};
