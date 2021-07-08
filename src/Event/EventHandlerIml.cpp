#include "EventHandlerIml.h"
#include "Event.h"

using namespace slt;

EventHandlerIml::EventHandlerIml(EventKey eventType, std::function<void(EventKey key, EventData &data, EventSender *)> onEvent, const std::string &name, EventSender * sender /* = nullptr*/)
    : EventHandler(eventType, sender, nullptr), m_onEventF(onEvent), m_name(name)
{

}

EventHandlerIml::~EventHandlerIml()
{
    printf("[EventHandlerIml]:%s is dead\n", this->m_name.c_str());
}

void EventHandlerIml::DispatchEvent(EventKey key, EventData &data, EventSender * sender)
{
    if (this->m_onEventF != nullptr) {
        this->m_onEventF(key, data, sender);
    }
}
