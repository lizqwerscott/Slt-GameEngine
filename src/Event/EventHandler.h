#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Event.h"

namespace slt
{
class EventSender;
class EventReciver;
class EventHandler
{
public:
	EventHandler(int eventType, EventSender * sender = nullptr, EventReciver * reciver = nullptr);
	virtual ~EventHandler();
public:
	virtual void DispatchEvent(EventKey &key, EventData &data, EventSender * sender);
public:
	int m_eventType;
	EventSender * m_sender;
	EventReciver * m_reciver;
};
}

#endif