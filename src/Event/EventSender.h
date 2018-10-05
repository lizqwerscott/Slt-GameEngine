#ifndef EVENTSENDER_H
#define EVENTSENDER_H

#include "Event.h"

namespace slt
{
class EventSender
{
public:
	virtual void SendEvent(EventKey &key, EventData &data);
};
}

#endif
