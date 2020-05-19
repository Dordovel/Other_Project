#include "../headers/core.hpp"

void Core::close() noexcept
{
    this->_window->window_close();
}

bool Core::is_run() noexcept
{
	return this->_window->is_open();
}

void Core::shutdown() noexcept
{
	this->_coreIsRun = false;
}

void Core::run() noexcept
{
	this->_coreIsRun = true;

    while (this->_window->is_open() && this->_coreIsRun)
    {
        if(this->_eventDispatcher)
        {
			std::shared_ptr<IEvents> eventHandler = this->_eventDispatcher->get_event_handler();

			if(eventHandler)
			{
				while (this->_window->event_handler(eventHandler->get_event_object()))
				{
					eventHandler->catch_events_loop();
				}
				
				eventHandler->catch_events_none();
			}
        }

		auto layout  = this->_layoutDispatcher->get_layout();
		auto object = this->_layoutDispatcher->get_object();

		if(layout.first)
		{
			if(layout.first->is_visible())
			{
				this->_window->draw(layout.first);
			}

			for(auto&& [id, child] : layout.second)
			{
				if(child->is_visible())
				{
					this->_window->draw(child);
				}
			}
		}

        for(auto&& [id, value] : object)
        {
            if (value->is_visible())
            {
                this->_window->draw(value);
            }
        }

        this->_window->display();
    }
}

void Core::register_app(const std::shared_ptr<IApplication>& window) noexcept
{
    this->_window = std::move(window);
}

void Core::set_event_dispatcher(const std::shared_ptr<IEventDispatcher>& eventDispatcher) noexcept
{
    this->_eventDispatcher= std::move(eventDispatcher);
}

void Core::set_layout_dispatcher(const std::shared_ptr<ILayoutDispatcher>& layoutDispatcher) noexcept
{
	this->_layoutDispatcher = layoutDispatcher;
}
