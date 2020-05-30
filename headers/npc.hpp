#pragma once 

#include "../Interface/inpc.hpp"
#include "../graphicobject/sprite.hpp"

class Npc : public Sprite, public INpc
{
	private:

		int _health = {0};
		float _damage = {0};
		float _armor = {0};
		int _points = {0};

	public:
        explicit Npc(const DataBaseResult& data);

		int get_health() const noexcept override;
		int get_points() const noexcept override;
		float get_damage() const noexcept override;
		float get_armor() const noexcept override;

		void set_health(int health) noexcept override;
		void set_points(int points) noexcept override;
		void set_armor(float armor) noexcept override;
		void set_damage(float damage) noexcept override;

		~Npc() = default;
};
