#include "../headers/npc.hpp"


Npc::Npc(const DataBaseResult& data):Sprite(data){}

int Npc::get_health() const noexcept
{
	return this->_health;
}

int Npc::get_points() const noexcept
{
	return this->_points;
}

float Npc::get_damage() const noexcept
{
	return this->_damage;
}

float Npc::get_armor() const noexcept
{
	return this->_armor;
}

void Npc::set_health(int health) noexcept
{
	this->_health = health;
}
void Npc::set_points(int points) noexcept
{
	this->_points = points;
}

void Npc::set_armor(float armor) noexcept
{
	this->_armor = armor;
}

void Npc::set_damage(float damage) noexcept
{
	this->_damage = damage;
}

