#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

namespace slt
{
class Event;
class EventSender;
class EventReciver;
class EventHandler
{
public:
	EventHandler(int eventType, EventSender * sender = nullptr, EventReciver * reciver = nullptr);
	virtual ~EventHandler();
public:
	virtual void DispatchEvent(Event * evt, EventSender * sender);
public:
	int m_eventType;
	EventSender * m_sender;
	EventReciver * m_reciver;
};
}

#endif