#include "../headers/npc_dispatcher.hpp"

namespace PROJECT::DISPATCHER
{
	void NpcDispatcher::delete_object(size_t index) noexcept
	{
		this->_object.erase(this->_object.begin() + index);
		this->_objectAnimation.erase(this->_objectAnimation.begin() + index);
		this->_sideGenerator.erase(this->_sideGenerator.begin() + index);
	}

	void NpcDispatcher::add_object(std::shared_ptr<NPC::INpc>&& object) noexcept
	{
		this->_object.emplace_back(std::move(object));
		this->_objectAnimation.emplace_back(ANIMATION_FRAME);
		this->_sideGenerator.emplace_back(10.F);
	}

	std::shared_ptr<NPC::INpc>& NpcDispatcher::object(int index) noexcept
	{
		return this->_object.at(index);
	}

	ANIMATION::Anim& NpcDispatcher::animation(int index) noexcept
	{
		return this->_objectAnimation.at(index);
	}

	MOVE::Side NpcDispatcher::side(int index, float time) noexcept
	{
		return this->_sideGenerator.at(index).generate(time);
	}

	size_t NpcDispatcher::size() const noexcept
   	{
		return this->_object.size();
	}

	bool NpcDispatcher::empty() const noexcept
	{
		return this->_object.empty();
	}
};
