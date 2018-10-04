#ifndef EVENTSENDER_H
#define EVENTSENDER_H

namespace slt
{
class Event;
class EventSender
{
public:
	virtual void SendEvent(Event * event);
};
}

#endif
