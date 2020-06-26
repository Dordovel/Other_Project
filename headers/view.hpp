#pragma once

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

        View(const PROJECT::BASE::DATA::Vector2F& position, float Width, float Height);

        View(const PROJECT::BASE::DATA::Vector2F& position, const PROJECT::BASE::DATA::Vector2F& size);

        View(const PROJECT::BASE::DATA::Vector2F& size);

        void zoom(float zoom) noexcept override;

        void set_position(const PROJECT::BASE::DATA::Vector2F& position) noexcept override;

        void set_position(float X, float Y) noexcept override;

        bool collision(const std::shared_ptr<INTERACTION>& object) noexcept override;

        bool collision(const PROJECT::BASE::DATA::Vector2F& vec) noexcept override;

        bool collision(const PROJECT::BASE::DATA::RectangleF& rect) noexcept override;

        void move(const PROJECT::BASE::DATA::Vector2F& step) noexcept override;

        void move(float X, float Y) noexcept override;

        PROJECT::BASE::DATA::Vector2F get_position() const noexcept override;

        PROJECT::BASE::DATA::RectangleF get_global_bounds() const noexcept override;

        PROJECT::BASE::DATA::Vector2F get_size() const noexcept override;

        void set_size(const PROJECT::BASE::DATA::Vector2F& size) noexcept override;

        void set_size(float x, float y) noexcept override;
      
        void block_side(PROJECT::MOVE::Side side, bool status) noexcept override;

        void block_all_side() noexcept override;

        void unblock_all_side() noexcept override;
      
        ~View() = default;
  };
};
