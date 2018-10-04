#include "EventHandlerIml.h"
#include "Event.h"

using namespace slt;

EventHandlerIml::EventHandlerIml(int eventType, std::function<void(Event *, EventSender *)> onEvent, EventSender * sender /* = nullptr*/)
	: EventHandler(eventType, sender, nullptr), m_onEventF(onEvent) 
{

}

EventHandlerIml::~EventHandlerIml()
{

}

void EventHandlerIml::DispatchEvent(Event * evt, EventSender * sender)
{
	if (this->m_onEventF != nullptr)
	{
		this->m_onEventF(evt, sender);
	}
}
