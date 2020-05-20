#pragma once 

#include "./ievents.hpp"
#include <memory>

class IEventDispatcher
{
	public:
		virtual bool register_event_handler(const std::shared_ptr<IEvents>& eventHandler) noexcept = 0;
		virtual void change_event_handler(const std::string& id) noexcept = 0;
		virtual std::shared_ptr<IEvents> get_event_handler() const noexcept = 0;

		virtual ~IEventDispatcher() = default;
};
