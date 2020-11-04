#ifndef SFMLPROJECT_REBUILD_VIEW_HPP
#define SFMLPROJECT_REBUILD_VIEW_HPP

#include "../Interface/iview.hpp"
#include <SFML/Graphics/View.hpp>

namespace PROJECT::APPLICATION
{
  class View final : public PROJECT::APPLICATION::IView, public sf::View
  {
    private:
      bool _up;
      bool _down;
      bool _left;
      bool _right;

      public:
      
        View() = default;

        View(float X, float Y, float Width, float Height);

        View(PROJECT::BASE::DATA::Vector2F position, float Width, float Height);

        View(PROJECT::BASE::DATA::Vector2F position, PROJECT::BASE::DATA::Vector2F size);

        View(PROJECT::BASE::DATA::Vector2F size);

        void zoom(float zoom) noexcept override;

        void set_position(PROJECT::BASE::DATA::Vector2F position) noexcept override;

        void set_position(float X, float Y) noexcept override;

        bool collision(const INTERACTION* const object) const noexcept override;

        bool collision(const PROJECT::BASE::DATA::Vector2F vec) const noexcept override;

        bool collision(const PROJECT::BASE::DATA::RectangleF rect) const noexcept override;

        void move(PROJECT::BASE::DATA::Vector2F step) noexcept override;

        void move(float X, float Y) noexcept override;

        PROJECT::BASE::DATA::Vector2F get_position() const noexcept override;

        PROJECT::BASE::DATA::RectangleF get_global_bounds() const noexcept override;

        PROJECT::BASE::DATA::Vector2F get_size() const noexcept override;

        void set_size(PROJECT::BASE::DATA::Vector2F size) noexcept override;

        void set_size(float x, float y) noexcept override;
      
        void block_side(PROJECT::MOVE::Side side, bool status) noexcept override;

        void block_all_side() noexcept override;

        void unblock_all_side() noexcept override;
      
        ~View() = default;
  };
};
#endif //SFMLPROJECT_REBUILD_VIEW_HPP
