#include "EventSender.h"
#include "EventManager.h"

using namespace slt;

void EventSender::SendEvent(Event * evt)
{
	EventManager::Instance()->DispatchEvent(evt, this);
}
