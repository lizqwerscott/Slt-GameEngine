#ifndef EVENTRECIVER_H
#define EVENTRECIVER_H

#include "Event.h"

namespace slt
{
class EventSender;
class EventReciver
{
public:
	virtual void OnEvent(EventSender * sender, EventKey key, EventData &data);
};
}

#endif
