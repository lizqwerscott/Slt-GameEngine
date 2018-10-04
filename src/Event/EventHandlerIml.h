#ifndef EVENTHANDLERIML_H
#define EVENTHANDLERIML_H

#include <functional>
#include "EventHandler.h"

namespace slt
{
class EventHandlerIml : public EventHandler
{
public:
	EventHandlerIml(int eventType, std::function<void(Event *, EventSender *)> onEvent, EventSender * sender = nullptr);
	~EventHandlerIml();
public:
	virtual void DispatchEvent(Event * evt, EventSender * sender);
public:
	std::function<void(Event *, EventSender *)> m_onEventF;
};
}

#endif
