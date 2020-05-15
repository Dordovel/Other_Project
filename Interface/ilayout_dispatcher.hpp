#pragma once

#include "../object/drawable.hpp"
#include <string> 
#include <memory>
#include <map>
#include <vector>

class ILayoutDispatcher
{
	public:
        virtual bool add_layout(const std::string& id, const std::shared_ptr<DRAWABLE>& object) = 0;
        virtual bool add_object(const std::string& id, const std::shared_ptr<DRAWABLE>& object) = 0;
        virtual bool insert_layout_child(const std::string& parent_id, const std::string& child_id, const std::shared_ptr<DRAWABLE>& object) = 0;
        virtual void remove_layout(const std::string& id) = 0;
        virtual void remove_object(const std::string& id) = 0;
		virtual void change_layout(const std::string& layoutName) = 0;
		virtual std::pair<std::shared_ptr<DRAWABLE>, std::vector<std::shared_ptr<DRAWABLE>>>
			get_layout() const = 0;
		virtual std::vector<std::shared_ptr<DRAWABLE>> get_object() const = 0;
	
		virtual ~ILayoutDispatcher() = default;
};	
