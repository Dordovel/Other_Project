#include "../headers/layout_dispatcher.hpp"


bool LayoutDispatcher::add_layout(const std::string& id, const std::shared_ptr<ILayout>& object)
{
    std::map<std::string, std::shared_ptr<OBJECT>> data{};
    auto insert_result = this->_layout.emplace(id, std::make_pair(object, data));

    return insert_result.second;
}

bool LayoutDispatcher::add_object(const std::string& id, const std::shared_ptr<OBJECT>& object)
{
    auto result = this->_object.emplace(id, object);
    return result.second;
}

void LayoutDispatcher::remove_layout(const std::string& id)
{
    this->_layout.erase(id);
}

void LayoutDispatcher::remove_layout_child(const std::string& layout_id, const std::string& child_id)
{
	auto result = this->_layout.find(layout_id);
	if(result != this->_layout.end())
	{
		result->second.second.erase(child_id);
	}
}

void LayoutDispatcher::remove_object(const std::string& id)
{
    this->_object.erase(id);
}

bool LayoutDispatcher::insert_layout_child(const std::string& parent_id, const std::string& child_id, const std::shared_ptr<OBJECT>& object)
{
    auto result = this->_layout.find(parent_id);
    if (result != this->_layout.end())
    {
        auto insert_result = result->second.second.emplace(child_id, object);
        return insert_result.second;
    }
    else
    {
        return false;
    }
}

std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
	LayoutDispatcher::get_layout() const
{
	std::pair <std::shared_ptr<ILayout>, std::map< std::string, std::shared_ptr<OBJECT>>> result;

	auto searchValue = this->_layout.find(this->_currentLayout);
	if(searchValue != this->_layout.end())
	{
		result.first = searchValue->second.first;
		for(auto&&  [id, object] : searchValue->second.second)
		{
			result.second.emplace(id, object);
		}
	}

	return result;
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

void LayoutDispatcher::change_layout(const std::string& layoutName)
{
	this->_layoutHistory.push_back(this->_currentLayout);
	this->_currentLayout = layoutName;
}

std::string LayoutDispatcher::get_current_layout_id() const
{
	return this->_currentLayout;
}

std::vector<std::string> LayoutDispatcher::get_change_history() const
{
	return this->_layoutHistory;
}
