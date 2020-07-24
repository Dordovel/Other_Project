#ifndef SFMLPROJECT_REBUILD_NPC_HPP
#define SFMLPROJECT_REBUILD_NPC_HPP

#include "../Interface/inpc.hpp"
#include "../graphicobject/sprite.hpp"
#include "./animation.hpp"
#include <map>

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
			std::map<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation> _animWalk;
			std::map<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation> _animAttack;

			State _state;

		public:
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

			State get_state() noexcept override;

			void set_state(State state) noexcept override;

			void add_animation_walk(PROJECT::MOVE::Side side,
									const std::array<PROJECT::BASE::DATA::RectangleI, 3>& rect) noexcept;

			void add_animation_attack(PROJECT::MOVE::Side side,
										const std::array<PROJECT::BASE::DATA::RectangleI, 3>& rect) noexcept;

			PROJECT::ANIMATION::IAnimation* get_animation_attack(PROJECT::MOVE::Side side) noexcept override;

			PROJECT::ANIMATION::IAnimation* get_animation_walk(PROJECT::MOVE::Side side) noexcept override;

			explicit Npc(const PROJECT::DATABASE::DataBaseResult& data);

			Npc(const Npc&) = default;

			Npc(Npc&&) = default;
			
			Npc& operator= (const Npc&) = default;

			Npc& operator= (Npc&&) = default;

            ~Npc() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_NPC_HPP
