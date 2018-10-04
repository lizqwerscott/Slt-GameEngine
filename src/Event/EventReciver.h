#ifndef EVENTRECIVER_H
#define EVENTRECIVER_H

namespace slt
{
class Event;
class EventSender;
class EventReciver
{
public:
	virtual void OnEvent(EventSender * sender, Event * evt);
};
}

#endif
