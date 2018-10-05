#include "EventHandlerIml.h"
#include "Event.h"

using namespace slt;

EventHandlerIml::EventHandlerIml(int eventType, std::function<void(EventKey &key, EventData &data, EventSender *)> onEvent, EventSender * sender /* = nullptr*/)
	: EventHandler(eventType, sender, nullptr), m_onEventF(onEvent) 
{

}

EventHandlerIml::~EventHandlerIml()
{

}

void EventHandlerIml::DispatchEvent(EventKey &key, EventData &data, EventSender * sender)
{
	if (this->m_onEventF != nullptr)
	{
		this->m_onEventF(key, data, sender);
	}
}
