#pragma once

#include "../Interface/ilayout_dispatcher.hpp"

class LayoutDispatcher final : public ILayoutDispatcher
{
	private:
        std::map<std::string, std::shared_ptr<OBJECT>> _layoutChilds;
        std::map<std::string, std::shared_ptr<OBJECT>> _object;
		std::shared_ptr<ILayout> _layout;


	public:
		void set_layout(const std::shared_ptr<ILayout>& object) noexcept override;

		bool add_object(const std::shared_ptr<OBJECT>& object) noexcept override;

		void remove_layout_child(const std::string& child_id) noexcept override;

		bool insert_layout_child(const std::shared_ptr<OBJECT>& object) noexcept override;

		void remove_object(const std::string& id) noexcept override;

		std::pair<std::shared_ptr<ILayout>, std::map<std::string, std::shared_ptr<OBJECT>>>
			get_layout() const noexcept override;
		
		std::map<std::string, std::shared_ptr<OBJECT>> get_object() const noexcept override;

		std::string get_current_layout_id() const noexcept override;

		~LayoutDispatcher() = default;
		LayoutDispatcher() = default;
};
