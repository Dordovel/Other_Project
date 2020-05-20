#include "../headers/layout_dispatcher.hpp"


void LayoutDispatcher::set_layout(const std::shared_ptr<ILayout>& object)
{
	this->_layout = object;
}

bool LayoutDispatcher::add_object(const std::shared_ptr<OBJECT>& object)
{
    auto result = this->_object.emplace(object->get_id(), object);
    return result.second;
}

void LayoutDispatcher::remove_layout_child(const std::string& child_id)
{
	this->_layoutChilds.erase(child_id);
}

void LayoutDispatcher::remove_object(const std::string& id)
{
    this->_object.erase(id);
}

bool LayoutDispatcher::insert_layout_child(const std::shared_ptr<OBJECT>& object)
{
	return this->_layoutChilds.emplace(object->get_id(), object).second;
}

std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
	LayoutDispatcher::get_layout() const
{
	return std::make_pair(this->_layout, this->_layoutChilds);
}

std::map<std::string, std::shared_ptr<OBJECT>> LayoutDispatcher::get_object() const
{
	std::map<std::string, std::shared_ptr<OBJECT>> result;
	
	for(auto&& [id, object] : this->_object)
	{
		result.emplace(id, object);
	}

	return result;
}

std::string LayoutDispatcher::get_current_layout_id() const
{
	return this->_layout->get_id();
}

