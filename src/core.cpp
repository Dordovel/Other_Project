#include "../headers/core.hpp"

void Core::close() noexcept
{
    this->_window->window_close();
}

bool Core::is_run() noexcept
{
	return this->_window->is_open();
}

void Core::interrupt() noexcept
{
	this->_coreIsRun = false;
}

void Core::run()
{
	this->_coreIsRun = true;

    while (this->_window->is_open() && this->_coreIsRun)
    {
        if(this->_eventDispatcher)
        {
			while (this->_window->event_handler(this->_eventDispatcher->get_event_object()))
			{
				this->_eventDispatcher->catch_events_loop();
			}
			
			this->_eventDispatcher->catch_events_none();
        }

		if(this->_layoutDispatcher)
		{
			auto layout = this->_layoutDispatcher->get_layout();
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
		}

        this->_window->display();
    }
}

void Core::register_app(const std::shared_ptr<IApplication>& window) noexcept
{
    this->_window = std::move(window);
}

void Core::set_event_dispatcher(const std::shared_ptr<IEvents>& eventDispatcher) noexcept
{
    this->_eventDispatcher = eventDispatcher;
}

void Core::set_layout_dispatcher(const std::shared_ptr<ILayoutDispatcher>& layoutDispatcher) noexcept
{
	this->_layoutDispatcher = layoutDispatcher;
}

void Core::remove_layout_dispatcher() noexcept
{
	this->_layoutDispatcher = nullptr;
}

void Core::remove_event_dispatcher() noexcept
{
	this->_eventDispatcher = nullptr;
}
