#include "Event.h"

using namespace slt;

Event::Event(int evenyKey) : m_eventKey(evenyKey)
{

}

Event::~Event()
{

}

int Event::getEventKey() {
	return this->m_eventKey;
}

