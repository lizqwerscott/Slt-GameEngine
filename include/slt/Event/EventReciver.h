#ifndef EVENTRECIVER_H
#define EVENTRECIVER_H

#include "Event.h"

namespace slt
{
class EventSender;
class EventReciver
{
public:
    virtual void OnEvent(EventKey key, EventData &data, EventSender * sender);
};
}

#endif
