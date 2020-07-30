#include "../headers/chest.hpp"
#include <cmath>

namespace PROJECT::CHEST
{
	Chest::Chest(const PROJECT::DATABASE::DataBaseResult& data):PROJECT::BASE::GRAPHIC::Sprite(data){}

	void Chest::add_elements(std::shared_ptr<OBJECT>&& element) noexcept
	{
		this->_elements.emplace_back(std::move(element));
		this->_isMod = true;
	}

	std::vector<std::shared_ptr<OBJECT>> Chest::get_elements_on_page() noexcept
	{
		this->_begin = (this->_currentPage - 1) * this->_elementOnPage;
		size_t _lastIndex = this->_currentPage * this->_elementOnPage;
		size_t _end;

		if(_lastIndex <= this->_elements.size())
			_end = _lastIndex;
		else
			_end = this->_elements.size();	

		std::vector<std::shared_ptr<OBJECT>> result(std::next(this->_elements.begin(), this->_begin),
													std::next(this->_elements.begin(), _end));

		++this->_begin;
		return result;
	}

	void Chest::delete_element(size_t index) noexcept
	{
		this->_elements.erase(std::next(this->_elements.begin(), index));
		this->_isMod = true;
		this->sort();
	}

	size_t Chest::size() const noexcept
	{
		return this->_elements.size();
	}

	bool Chest::is_empty() const noexcept
	{
		return this->_elements.empty();
	}

	int Chest::get_page() const noexcept
	{
		return this->_currentPage;
	}

	void Chest::page_back() noexcept
	{
		if(this->_currentPage > 1)
			this->_currentPage--;
	}

	void Chest::page_forward() noexcept
	{
		if(this->_currentPage < this->_pageCout)
			this->_currentPage++;
	}

	void Chest::set_page_position(float x, float y, float width, float height) noexcept
	{
		this->_grid.init(x, y, width, height);
	}

	void Chest::sort() noexcept
	{
		if(this->_isMod)
		{
			size_t unsortedElement = this->_grid.sort(this->_elements);

			if(unsortedElement > 0)
			{
				this->_elementOnPage = this->_elements.size() - unsortedElement;

				this->_pageCout = std::ceil((float)this->_elements.size() / (float)this->_elementOnPage);

				for(int page = 1; page <= this->_pageCout; ++page)
				{
					this->_currentPage = page;

					auto collection = this->get_elements_on_page();
		
					this->_grid.sort(collection);
				}

				this->_currentPage = 1;

				this->_isMod = false;
			}
			else
			{
				this->_elementOnPage = this->_elements.size();
				this->_pageCout = 1;
				this->_currentPage = 1;
			}
			
		}
	}
};

