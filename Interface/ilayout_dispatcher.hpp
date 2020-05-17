#pragma once

#include "../object/object.hpp"
#include <string> 
#include <memory>
#include <map>
#include "./ilayout.hpp"

class ILayoutDispatcher
{
	public:
        virtual bool add_layout(const std::string& id, const std::shared_ptr<ILayout>& object) = 0;
        virtual bool add_object(const std::string& id, const std::shared_ptr<OBJECT>& object) = 0;
        virtual bool insert_layout_child(const std::string& parent_id, const std::string& child_id, const std::shared_ptr<OBJECT>& object) = 0;
        virtual void remove_layout(const std::string& id) = 0;
        virtual void remove_object(const std::string& id) = 0;
		virtual void remove_layout_child(const std::string& layout_id, const std::string& child_id) = 0;
		virtual void change_layout(const std::string& layoutName) = 0;
		virtual std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
			get_layout() const = 0;
		virtual std::map<std::string, std::shared_ptr<OBJECT>> get_object() const = 0;

		virtual std::string get_current_layout_id() = 0;
	
		virtual ~ILayoutDispatcher() = default;
};	
