#pragma once 

class INpc
{
	public:

		virtual int get_health() const noexcept = 0;
		virtual int get_points() const noexcept = 0;
		virtual float get_damage() const noexcept = 0;
		virtual float get_armor() const noexcept = 0;

		virtual void set_health(int health) noexcept = 0;
		virtual void set_points(int points) noexcept = 0;
		virtual void set_armor(float armor) noexcept = 0;
		virtual void set_damage(float damage) noexcept = 0;

		virtual ~INpc() = default;
};
