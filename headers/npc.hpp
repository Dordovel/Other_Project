#ifndef SFMLPROJECT_REBUILD_NPC_HPP
#define SFMLPROJECT_REBUILD_NPC_HPP

#include "../Interface/inpc.hpp"
#include "../graphicobject/sprite.hpp"
#include "./animation.hpp"
#include <vector>

namespace PROJECT::NPC
{
	class Npc : public INpc,
				public PROJECT::BASE::GRAPHIC::Sprite

	{
		private:
			float _armor = {0};
			float _damage = {0};
			int _health = {-1};
			int _maxHealth = {-1};
			int _points = {-1};
			std::vector<std::pair<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation>> _animWalk;
			std::vector<std::pair<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation>> _animAttack;
			std::vector<std::pair<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation>> _animIdle;

			State _state;

			float _viewRadius;

		public:

			explicit Npc(const PROJECT::DATABASE::DataBaseResult& data);

			Npc(const Npc&) = default;

			Npc(Npc&&) = default;
			
			Npc& operator= (const Npc&) = default;

			Npc& operator= (Npc&&) = default;

			float get_armor() const noexcept override;

			void set_armor(float armor) noexcept override;

			float get_damage() const noexcept override;

			void set_damage(float damage) noexcept override;

			int get_max_health() const noexcept override;

			void set_max_health(int health) noexcept override;

			int get_health() const noexcept override;

			void set_health(int health) noexcept override;

			int get_points() const noexcept override;

			void set_points(int points) noexcept override;

			State get_state() const noexcept override;

			void set_state(State state) noexcept override;

			float get_view_radius() const noexcept override;

			void set_view_radius(float radius) noexcept override;

			void add_animation_walk(PROJECT::MOVE::Side side,
									std::array<PROJECT::BASE::DATA::RectangleI, 3> rect) noexcept;

			void add_animation_attack(PROJECT::MOVE::Side side,
										std::array<PROJECT::BASE::DATA::RectangleI, 3> rect) noexcept;

			void add_animation_idle(PROJECT::MOVE::Side side,
										std::array<PROJECT::BASE::DATA::RectangleI, 3> rect) noexcept;

			PROJECT::ANIMATION::IAnimation* get_animation_attack(PROJECT::MOVE::Side side) noexcept override;

			PROJECT::ANIMATION::IAnimation* get_animation_walk(PROJECT::MOVE::Side side) noexcept override;

			PROJECT::ANIMATION::IAnimation* get_animation_idle(PROJECT::MOVE::Side side) noexcept override;

            ~Npc() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_NPC_HPP
