#ifndef EventManager_H
#define EventManager_H

#include <list>
#include <map>

#define SubscribeEventIml(key, fu, sender) EventManager::Instance()->AddEventHandler(key, (new EventHandlerIml(key, fu, sender)))

#define SubscribeEvent(key, sender, reciver) EventManager::Instance()->AddEventHandler(key, (new EventHandler(key, sender, reciver)))

namespace slt
{
class Event;
class EventHandler;
class EventSender;
class EventManager
{
	typedef std::list<EventHandler *> HandlerList;
	typedef std::map<int, HandlerList> IdHandlerMap;
public:
	static EventManager * Instance();
	static void Destory();

	void AddEventHandler(int id, EventHandler * handler);
	void RemoveEventHandler(int id, EventHandler *handler);
	void ClearEventHandler(int id);
	void DispatchEvent(Event * evt, EventSender * sender = nullptr);
private:
	EventManager() {}
	EventManager(const EventManager *) {}
	~EventManager();
private:
	//int m_nowEventKeyNumber; //Rember now best key.we can create a new key when we registered a new Event
	IdHandlerMap m_events;
};
}

#endif