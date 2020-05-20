#include "../headers/event_dispatcher.hpp"

bool EventDispatcher::register_event_handler(const std::shared_ptr<IEvents>& eventHandler) noexcept
{
	auto result = this->_events.emplace(eventHandler->get_id(), eventHandler);
	return result.second;
}

void EventDispatcher::change_event_handler(const std::string& id) noexcept
{
	this->_currentEventHandler = id;
}

std::shared_ptr<IEvents> EventDispatcher::get_event_handler() const noexcept
{
	std::shared_ptr<IEvents> result;

	auto value = this->_events.find(this->_currentEventHandler);

	if(value != this->_events.end())
	{
		result = value->second;
	}

	return result;
}
