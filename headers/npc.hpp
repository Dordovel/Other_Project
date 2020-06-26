#pragma once
#include "../Interface/inpc.hpp"
#include "../graphicobject/sprite.hpp"
#include "./animation.hpp"
#include <map>

namespace PROJECT::NPC
{
	class Npc : public PROJECT::BASE::GRAPHIC::Sprite, public INpc
	{
		private:
			float _armor = {0};
			float _damage = {0};
			int _health = {-1};
			int _maxHealth = {-1};
			int _points = {-1};
			std::map<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation> _animWalk;
			std::map<PROJECT::MOVE::Side, PROJECT::ANIMATION::Animation> _animAttack;

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

			explicit Npc(const PROJECT::DATABASE::DataBaseResult& data, std::string_view id);

			void add_animation_walk(PROJECT::MOVE::Side side, const std::array<PROJECT::BASE::DATA::RectangleI, 3>& rect) noexcept;

			void add_animation_attack(PROJECT::MOVE::Side side, const std::array<PROJECT::BASE::DATA::RectangleI, 3>& rect) noexcept;


			PROJECT::ANIMATION::IAnimation& get_animation_attack(PROJECT::MOVE::Side side) noexcept override;

			PROJECT::ANIMATION::IAnimation& get_animation_walk(PROJECT::MOVE::Side side) noexcept override;

			~Npc() = default;
	};
};
