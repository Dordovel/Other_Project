#pragma once

#include "../Interface/ilayout_dispatcher.hpp"

class LayoutDispatcher : public ILayoutDispatcher
{
	private:
        std::map<std::string, std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>> _layout;
        std::map<std::string, std::shared_ptr<OBJECT>> _object;
		std::string _currentLayout;
		std::vector<std::string> _layoutHistory;

	public:
		bool add_layout(const std::string& id, const std::shared_ptr<ILayout>& object) override;

		bool add_object(const std::string& id, const std::shared_ptr<OBJECT>& object) override;

		void remove_layout(const std::string& id) override;

		void remove_layout_child(const std::string& layout_id, const std::string& child_id) override;

		bool insert_layout_child(const std::string& parent_id, const std::string& child_id, const std::shared_ptr<OBJECT>& object) override;

		void remove_object(const std::string& id) override;

		void change_layout(const std::string& layoutName) override;

		std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
			get_layout() const override;
		
		std::map<std::string, std::shared_ptr<OBJECT>> get_object() const override;

		std::string get_current_layout_id() const override;

		std::vector<std::string> get_change_history() const override;

		~LayoutDispatcher() = default;
		LayoutDispatcher() = default;
};
