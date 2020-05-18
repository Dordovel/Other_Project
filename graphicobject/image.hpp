#pragma once
#include <map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../struct/databaseresult.hpp"
#include <memory>
#include "../object/scalable.hpp"
#include "../object/object.hpp"

class Image : public OBJECT, public SCALABLE
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
        explicit Image(const DataBaseResult& data);

        DrawableObject draw() const override;

        ~Image() override = default;

        void move(const Vector2F& step) override;

        void move(float X, float Y) override;

        void set_position(const Vector2F& position) override;

        void set_position(float X, float Y) override;

        Vector2F get_position() const override;

        void rotate(float angle) override;

        RectangleF get_global_bounds() const override;

        bool collision(const std::shared_ptr<INTERACTION>& object) override;
		
        bool collision(const Vector2F& object) override;

        void set_id(const std::string& name) override;

        void visible(bool flag) override;

        bool is_visible() override;

		void set_scale(Vector2F scale) override;

		Vector2F get_scale() override;

        std::string get_id() const override;

		void block_side(SIDE side, bool status) override;
};
