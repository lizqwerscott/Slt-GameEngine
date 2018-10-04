#ifndef EVENT_H
#define EVENT_H

namespace slt
{
class Event
{
public:
	Event(int evenyKey);
	~Event();

	int getEventKey();
private:
	int m_eventKey;
	//params
};
}

#endif
