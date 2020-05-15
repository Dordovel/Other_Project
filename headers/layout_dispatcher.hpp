#pragma once

#include "../Interface/ilayout_dispatcher.hpp"

class LayoutDispatcher : public ILayoutDispatcher
{
	private:
        std::map<std::string, std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<DRAWABLE>>>> _layout;
        std::map<std::string, std::shared_ptr<DRAWABLE>> _object;
		std::string _currentLayout;

	public:
		bool add_layout(const std::string& id, const std::shared_ptr<ILayout>& object) override;

		bool add_object(const std::string& id, const std::shared_ptr<DRAWABLE>& object) override;

		void remove_layout(const std::string& id) override;

		bool insert_layout_child(const std::string& parent_id, const std::string& child_id, const std::shared_ptr<DRAWABLE>& object) override;

		void remove_object(const std::string& id) override;

		void change_layout(const std::string& layoutName) override;

		std::pair<std::shared_ptr<ILayout>, std::vector<std::shared_ptr<DRAWABLE>>>
			get_layout() const override;
		
		std::vector<std::shared_ptr<DRAWABLE>> get_object() const override;

		std::string get_current_layout_id() override;

		~LayoutDispatcher() = default;
		LayoutDispatcher() = default;
};
