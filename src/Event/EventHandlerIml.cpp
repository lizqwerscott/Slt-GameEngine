#include "slt/Event/EventHandlerIml.h"
#include "slt/Event/Event.h"

using namespace slt;

EventHandlerIml::EventHandlerIml(EventKey eventType, std::function<void(EventKey key, EventData &data, EventSender *)> onEvent, const std::string &name, EventSender * sender /* = nullptr*/)
    : EventHandler(eventType, sender, nullptr), m_onEventF(onEvent), m_name(name)
{

}

EventHandlerIml::~EventHandlerIml()
{
}

void EventHandlerIml::DispatchEvent(EventKey key, EventData &data, EventSender * sender)
{
    if (this->m_onEventF != nullptr) {
        this->m_onEventF(key, data, sender);
    }
}
