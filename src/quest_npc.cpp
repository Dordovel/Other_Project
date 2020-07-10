#include "headers/quest_npc.hpp"

namespace PROJECT::NPC
{
	QuestNpc::QuestNpc(const PROJECT::DATABASE::DataBaseResult& data):Sprite(data){}

	int QuestNpc::get_points() const noexcept
	{
		return this->_points;
	}

	void QuestNpc::set_points(int points) noexcept
	{
		this->_points = points;
	}
};
