#include "../object/object.hpp"
#include <vector>
#include "../headers/chest_dispatcher.hpp"

namespace PROJECT::DISPATCHER
{
	void ChestDispatcher::delete_object(size_t index) noexcept
	{
		this->_object.erase(std::next(this->_object.begin(), index));
	}

	void ChestDispatcher::add_object(std::shared_ptr<PROJECT::CHEST::IChest>&& object) noexcept
	{
		this->_object.emplace_back(std::move(object));
	}

	std::shared_ptr<PROJECT::CHEST::IChest>& ChestDispatcher::object(int index) noexcept
	{
		return this->_object.at(index);
	}

	size_t ChestDispatcher::size() const noexcept
	{
		return this->_object.size();
	}

	bool ChestDispatcher::empty() const noexcept
	{
		return this->_object.empty();
	}
};
