#include "../headers/chest.hpp"

namespace PROJECT::CHEST
{
	Chest::Chest(const PROJECT::DATABASE::DataBaseResult& data):PROJECT::BASE::GRAPHIC::Sprite(data){}

	void Chest::add_elements(std::shared_ptr<OBJECT>&& element) noexcept
	{
		this->_elements.emplace_back(std::move(element));
	}

	std::shared_ptr<OBJECT>& Chest::get_element(size_t index) noexcept
	{
		return this->_elements.at(index);
	}

	void Chest::delete_element(size_t index) noexcept
	{
		auto begin = this->_elements.begin();
		std::advance(begin, index);

		this->_elements.erase(begin);
	}

	size_t Chest::size() const noexcept
	{
		return this->_elements.size();
	}

	bool Chest::is_empty() const noexcept
	{
		return this->_elements.empty();
	}
};

