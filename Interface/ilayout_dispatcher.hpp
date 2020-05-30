#pragma once

#include "../object/object.hpp"
#include <string> 
#include <memory>
#include <map>
#include "./ilayout.hpp"

class ILayoutDispatcher
{
	public:
        virtual void set_layout(const std::shared_ptr<ILayout>& object) noexcept = 0;
        virtual bool add_object(const std::shared_ptr<OBJECT>& object) noexcept = 0;
        virtual bool insert_layout_child(const std::shared_ptr<OBJECT>& object) noexcept = 0;
        virtual void remove_object(const std::string& id) noexcept = 0;
		virtual void remove_layout_child(const std::string& child_id) noexcept = 0;
		virtual std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
			get_layout() const noexcept = 0;
		virtual std::map<std::string, std::shared_ptr<OBJECT>> get_object() const noexcept = 0;
		virtual std::string get_current_layout_id() const noexcept = 0;
	
		virtual ~ILayoutDispatcher() = default;
};	
