#ifndef EventManager_H
#define EventManager_H

#include <list>
#include "Event.h"
#include "../MemoryManager/AutoreleasePool.h"

namespace slt
{
class EventHandler;
class EventSender;
class EventManager
{
    typedef std::list<EventHandler *> HandlerList;
    typedef std::map<EventKey, EventData * > EventDataMap;
    typedef std::map<EventKey, HandlerList> IdHandlerMap;
public:
    static EventManager * Instance();
    static void Destory();

    void AddEventHandler(EventKey id, EventHandler * handler);
    void RemoveEventHandler(EventKey id, EventHandler *handler);
    void RemoveEventHandlerIml(EventKey id, const std::string &name);
    void ClearEventHandler(EventKey id);
    void DispatchEvent(EventKey key, EventData &data, EventSender * sender = nullptr);

    EventData &GetEventData(EventKey id);

private:
    EventManager() : m_pool (new AutoreleasePool("event")) {}
    EventManager(const EventManager *) {}
    ~EventManager();
private:
    //int m_nowEventKeyNumber; //Rember now best key.we can create a new key when we registered a new Event
    IdHandlerMap m_events;
    EventDataMap m_dataMaps;
private:
    AutoreleasePool *m_pool;
};

struct EventNameRegistrar {
    /// Register an event name for hash reverse mapping.
    static EventKey RegisterEventName(const char * eventName);
    /// Return Event name or empty string if not found.
    static const std::string& GetEventName(EventKey eventID);
    /// Return Event name map.
    static std::map<EventKey, std::string>& GetEventNameMap();
};
}

//SubscribeEvent
#define SubscribeEventIml(key, fu, sender, name) EventManager::Instance()->AddEventHandler(key, (new EventHandlerIml(key, fu, name, sender)))
#define UnSubscribleEventIml(key, name) EventManager::Instance()->RemoveEventHandlerIml(key, name)
#define SubscribeEvent(key, sender, reciver) EventManager::Instance()->AddEventHandler(key, (new EventHandler(key, sender, reciver)))

//Event
#define SLT_EVENT(eventID, eventName) static const EventKey eventID = slt::EventNameRegistrar::RegisterEventName((char *)#eventName); namespace eventName
#define SLT_PARAM(paramID, paramName) static const EventKey paramID = slt::Math::bkdrHash((char *)#paramName)

#endif
