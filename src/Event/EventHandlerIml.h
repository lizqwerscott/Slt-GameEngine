#ifndef EVENTHANDLERIML_H
#define EVENTHANDLERIML_H

#include <functional>
#include "EventHandler.h"

namespace slt
{
class EventHandlerIml : public EventHandler
{
public:
    EventHandlerIml(EventKey eventType, std::function<void(EventKey key, EventData &data, EventSender *)> onEvent, const std::string &name, EventSender * sender = nullptr);
    ~EventHandlerIml();
public:
    virtual void DispatchEvent(EventKey key, EventData &data, EventSender * sender) override;
public:
    std::function<void(EventKey key, EventData &data, EventSender *)> m_onEventF;
    std::string m_name;
};
}

#endif
