#include "EventHandler.h"
#include "EventReciver.h"
#include "Event.h"

using namespace slt;

EventHandler::EventHandler(EventKey eventType, EventSender * sender/*=nullptr*/, EventReciver * reciver/*=nullptr*/) :
    m_eventType(eventType), m_sender(sender), m_reciver(reciver)
{

}

EventHandler::~EventHandler()
{

}

void EventHandler::DispatchEvent(EventKey key, EventData &data, EventSender * sender)
{
    this->m_reciver->OnEvent(key, data, sender);
}
