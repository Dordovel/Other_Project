#pragma once

#include "../object/drawable.hpp"
#include <vector>
#include <memory>
#include <map>
#include "./ievents.hpp"
#include "./iclock.hpp"
#include "./iapplication.hpp"
#include "./ilayout_dispatcher.hpp"

class ICore
{
    public:
        virtual void run() noexcept = 0;
        virtual bool is_run() noexcept = 0;
        virtual void interrupt() noexcept = 0;
        virtual void close() noexcept = 0;
        virtual void register_app(const std::shared_ptr<IApplication>& window) noexcept = 0;
        virtual void set_event_dispatcher(const std::shared_ptr<IEvents>& eventDispatcher) noexcept = 0;
        virtual void remove_event_dispatcher() noexcept = 0;
		virtual void set_layout_dispatcher(const std::shared_ptr<ILayoutDispatcher>& layoutDispatcher) noexcept = 0; 
		virtual void remove_layout_dispatcher() noexcept = 0; 
        virtual ~ICore() = default;
};
