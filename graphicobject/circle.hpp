#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

#include "../object/drawable.hpp"
#include "../Interface/iobject.hpp"
#include "../object/scalable.hpp"

class Circle : public IOBJECT, public DRAWABLE, public SCALABLE
{
    private:
        std::shared_ptr<sf::CircleShape> _circleShape;
        std::string _id;
        bool _isVisible;

    public:
        DrawableObject draw() const override;

        void set_id(const std::string& id) override;

        std::string get_id() const override;

        void set_position(const Vector2F& position) override;

        void set_position(float X, float Y) override;

        void rotate(float angle) override;

        bool collision(const std::shared_ptr<INTERACTION>& object) override;

        void move(const Vector2F& step) override;

        void move(float X, float Y) override;

        Vector2F get_position() const override;

        RectangleF get_global_bounds() const override;

        explicit Circle(float radius);

        void visible(bool flag) override;

        bool is_visible() override;

		void set_scale(Vector2F scale) override;

		Vector2F get_scale() override;

        ~Circle() = default;
};
