#include "../headers/dynamic_obejct_dispatcher.hpp"

namespace PROJECT::DISPATCHER
{
	void DynamicObjectDispatcher::delete_object(size_t index) noexcept
	{
		this->_object.erase(this->_object.begin() + index);
		this->_objectAnimation.erase(this->_objectAnimation.begin() + index);
		this->_sideGenerator.erase(this->_sideGenerator.begin() + index);
	}

	void DynamicObjectDispatcher::add_object(std::shared_ptr<NPC::INpc>&& object) noexcept
	{
		this->_object.emplace_back(std::forward<decltype(object)>(object));
		this->_objectAnimation.emplace_back(ANIMATION_FRAME);
		this->_objectAnimation.back().set_object(this->_object.back());
		this->_sideGenerator.emplace_back(10.F);
	}

	std::shared_ptr<NPC::INpc>& DynamicObjectDispatcher::object(int index) noexcept
	{
		return this->_object.at(index);
	}

	ANIMATION::Anim& DynamicObjectDispatcher::animation(int index) noexcept
	{
		return this->_objectAnimation.at(index);
	}

	MOVE::Side DynamicObjectDispatcher::side(int index, float time) noexcept
	{
		return this->_sideGenerator.at(index).generate(time);
	}

	size_t DynamicObjectDispatcher::size() const noexcept
   	{
		return this->_object.size();
	}
};
