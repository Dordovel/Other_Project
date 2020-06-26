#include "../headers/npc.hpp"

namespace PROJECT::NPC
{
	Npc::Npc(const PROJECT::DATABASE::DataBaseResult& data, std::string_view id):PROJECT::BASE::GRAPHIC::Sprite(data, id){}

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

	PROJECT::ANIMATION::IAnimation& Npc::get_animation_attack(PROJECT::MOVE::Side side) noexcept
	{
		return this->_animAttack[side]; //&(*value).second;	
	}

	PROJECT::ANIMATION::IAnimation& Npc::get_animation_walk(PROJECT::MOVE::Side side) noexcept
	{
		return this->_animWalk[side]; //&(*value).second;	
	}

	void Npc::add_animation_walk(PROJECT::MOVE::Side side, const std::array<PROJECT::BASE::DATA::RectangleI, 3>& rect) noexcept
	{
		ANIMATION::Animation animation;
		for(const auto& var : rect)
			animation.add_frame(var);

		this->_animWalk.emplace(side, animation);
	}

	void Npc::add_animation_attack(PROJECT::MOVE::Side side, const std::array<PROJECT::BASE::DATA::RectangleI, 3>& rect) noexcept
	{
		ANIMATION::Animation animation;
		for(const auto& var : rect)
			animation.add_frame(var);

		this->_animAttack.emplace(side, animation);
	}
};
