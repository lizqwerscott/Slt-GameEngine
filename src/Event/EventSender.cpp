#include "EventSender.h"
#include "EventManager.h"

using namespace slt;

void EventSender::SendEvent(EventKey &key, EventData &data)
{
	EventManager::Instance()->DispatchEvent(key, data, this);
}
