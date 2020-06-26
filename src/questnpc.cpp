#include "../headers/questnpc.hpp"

namespace PROJECT::NPC
{
	QuestNpc::QuestNpc(const PROJECT::DATABASE::DataBaseResult& data, std::string_view id):Sprite(data, id){}

	int QuestNpc::get_points() const noexcept
	{
		return this->_points;
	}

	void QuestNpc::set_points(int points) noexcept
	{
		this->_points = points;
	}
};
