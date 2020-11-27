#include "../headers/npc.hpp"

namespace PROJECT::NPC
{
	Npc::Npc(const PROJECT::DATABASE::DataBaseResult& data):PROJECT::BASE::GRAPHIC::Sprite(data){}

	float Npc::get_armor() const noexcept
	{
		return this->_armor;
	}

	void Npc::set_armor(float armor) noexcept
	{
		this->_armor = armor;
	}

	float Npc::get_damage() const noexcept
	{
		return this->_damage;
	}

	void Npc::set_damage(float damage) noexcept
	{
		this->_damage = damage;
	}

	int Npc::get_max_health() const noexcept
	{
		return this->_maxHealth;
	}

	void Npc::set_max_health(int health) noexcept
	{
		this->_maxHealth = health;
	}

	int Npc::get_health() const noexcept
	{
		return this->_health;
	}

	void Npc::set_health(int health) noexcept
	{
		this->_health = health;
	}

	int Npc::get_points() const noexcept
	{
		return this->_points;
	}

	void Npc::set_points(int points) noexcept
	{
		this->_points = points;
	}

	State Npc::get_state() const noexcept
	{
		return this->_state;
	}

	void Npc::set_state(State state) noexcept
	{
		this->_state = state;
	}

	float Npc::get_view_radius() const noexcept
	{
		return this->_viewRadius;
	}

	void Npc::set_view_radius(float radius) noexcept
	{
		this->_viewRadius = radius;
	}

	PROJECT::ANIMATION::IAnimation* Npc::get_animation_attack(PROJECT::MOVE::Side side) noexcept
	{
		auto&& comparator = [&side](auto&& value){return value.first == side;};
		auto&& result = std::find_if(std::begin(this->_animAttack), std::end(this->_animAttack), comparator);

		if(result != this->_animAttack.end())
				return &result->second;
		else
			return nullptr;
	}

	PROJECT::ANIMATION::IAnimation* Npc::get_animation_walk(PROJECT::MOVE::Side side) noexcept
	{
		auto&& comparator = [&side](auto&& value){return value.first == side;};
		auto&& result = std::find_if(std::begin(this->_animWalk), std::end(this->_animWalk), comparator);

		if(result != this->_animWalk.end())
				return &result->second;
		else
			return nullptr;
	}

	PROJECT::ANIMATION::IAnimation* Npc::get_animation_idle(PROJECT::MOVE::Side side) noexcept
	{
		auto&& comparator = [&side](auto&& value){return value.first == side;};
		auto&& result = std::find_if(std::begin(this->_animIdle), std::end(this->_animIdle), comparator);

		if(result != this->_animIdle.end())
				return &result->second;
		else
			return nullptr;
	}

	void Npc::add_animation_walk(PROJECT::MOVE::Side side, std::array<PROJECT::BASE::DATA::RectangleI, 3> rect) noexcept
	{
		ANIMATION::Animation animation;
		animation.set_object(this);
		for(const auto& var : rect)
			animation.add_frame(var);

		this->_animWalk.emplace_back(side, animation);
	}

	void Npc::add_animation_attack(PROJECT::MOVE::Side side, std::array<PROJECT::BASE::DATA::RectangleI, 3> rect) noexcept
	{
		ANIMATION::Animation animation;
		animation.set_object(this);
		for(const auto& var : rect)
			animation.add_frame(var);

		this->_animAttack.emplace_back(side, animation);
	}

	void Npc::add_animation_idle(PROJECT::MOVE::Side side, std::array<PROJECT::BASE::DATA::RectangleI, 3> rect) noexcept
	{
		ANIMATION::Animation animation;
		animation.set_object(this);
		for(const auto& var : rect)
			animation.add_frame(var);

		this->_animIdle.emplace_back(side, animation);
	}
};
