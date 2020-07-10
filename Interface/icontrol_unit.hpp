#ifndef SFMLPROJECT_REBUILD_CONTROL_UNIT_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_CONTROL_UNIT_INTERFACE_HPP

#include <functional>

namespace PROJECT::EVENT
{
    class EventObject;
};

namespace PROJECT::UNIT::CONTROL
{
    enum class EventHandlerType
    {
        EVENT_LOOP,
        NONE
    };

    class IControlUnit
    {
        public:
            virtual void catch_events(const PROJECT::EVENT::EventObject& event) = 0;
            virtual ~IControlUnit() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_CONTROL_UNIT_INTERFACE_HPP
