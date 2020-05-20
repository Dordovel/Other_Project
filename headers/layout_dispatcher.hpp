#pragma once

#include "../Interface/ilayout_dispatcher.hpp"

class LayoutDispatcher : public ILayoutDispatcher
{
	private:
        std::map<std::string, std::shared_ptr<OBJECT>> _layoutChilds;
        std::map<std::string, std::shared_ptr<OBJECT>> _object;
		std::shared_ptr<ILayout> _layout;


	public:
		void set_layout(const std::shared_ptr<ILayout>& object) override;

		bool add_object(const std::shared_ptr<OBJECT>& object) override;

		void remove_layout_child(const std::string& child_id) override;

		bool insert_layout_child(const std::shared_ptr<OBJECT>& object) override;

		void remove_object(const std::string& id) override;

		std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
			get_layout() const override;
		
		std::map<std::string, std::shared_ptr<OBJECT>> get_object() const override;

		std::string get_current_layout_id() const override;

		~LayoutDispatcher() = default;
		LayoutDispatcher() = default;
};
