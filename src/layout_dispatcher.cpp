#include "../headers/layout_dispatcher.hpp"
#include <iostream>

void LayoutDispatcher::set_layout(const std::shared_ptr<ILayout>& object) noexcept
{
	this->_layout = object;
	this->_layoutChilds.clear();
}

bool LayoutDispatcher::add_object(const std::shared_ptr<OBJECT>& object) noexcept
{
    auto result = this->_object.emplace(object->get_id(), object);
    return result.second;
}

void LayoutDispatcher::remove_layout_child(const std::string& child_id) noexcept
{
	this->_layoutChilds.erase(child_id);
}

void LayoutDispatcher::remove_object(const std::string& id) noexcept
{
    this->_object.erase(id);
}

bool LayoutDispatcher::insert_layout_child(const std::shared_ptr<OBJECT>& object) noexcept
{
	return this->_layoutChilds.emplace(object->get_id(), object).second;
}

std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
	LayoutDispatcher::get_layout() const noexcept
{
	return std::make_pair(this->_layout, this->_layoutChilds);
}

std::map<std::string, std::shared_ptr<OBJECT>> LayoutDispatcher::get_object() const noexcept
{
	std::map<std::string, std::shared_ptr<OBJECT>> result;
	
	for(auto&& [id, object] : this->_object)
	{
		result.emplace(id, object);
	}

	return result;
}

std::string LayoutDispatcher::get_current_layout_id() const noexcept
{
	return this->_layout->get_id();
}

