#pragma once

#include "../Interface/ievent_dispatcher.hpp"
#include <map>

class EventDispatcher : public IEventDispatcher
{
	private:
		std::map<std::string, std::shared_ptr<IEvents>> _events;
		std::string _currentEventHandler;

	public:
		 bool register_event_handler(const std::shared_ptr<IEvents>& eventHandler) noexcept override;
		 void change_event_handler(const std::string& id) noexcept override;
		 std::shared_ptr<IEvents> get_event_handler() const noexcept override;

		 EventDispatcher() = default;
		 ~EventDispatcher() = default;
};
