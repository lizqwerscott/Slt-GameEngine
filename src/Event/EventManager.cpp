#include "EventManager.h"
#include "Event.h"
#include "EventHandler.h"
#include "EventSender.h"
#include "EventReciver.h"
#include "../Math/Math.h"
#include <memory>
#include <functional>

using namespace slt;

EventManager * eventManager = nullptr;

EventManager * 
EventManager::Instance()
{
	if (eventManager == nullptr)
	{
		eventManager = new EventManager();
	}
	return eventManager;
}

void EventManager::Destory()
{
	if (eventManager != nullptr)
	{
		delete eventManager;
	}
}

EventManager::~EventManager()
{
	for (auto mapIt : this->m_events)
	{
		for (auto listIt : mapIt.second)
		{
			delete listIt;
		}
	}
	for (auto mapIt : this->m_dataMaps)
	{
		delete mapIt.second;
	}
	this->m_events.clear();
	this->m_dataMaps.clear();
}

void EventManager::AddEventHandler(EventKey id, EventHandler * handler)
{
	if (handler == nullptr)
	{
		printf("Error::EventManager::AddEventHandler()::The EventHandle is nullptr\n");
		return;
	}
	auto pair = m_events.insert(std::make_pair(id, HandlerList()));
	auto it = pair.first;
	if (it == m_events.end())
	{
		printf("Error::EventManager::AddEventHandler()::It is the end, HandlerList insert error\n");
		return;
	}
	it->second.push_back(handler);
}

void EventManager::RemoveEventHandler(EventKey id, EventHandler * handler)
{
	if (handler == nullptr)
		return;
	auto it = m_events.find(id);
	if (it == m_events.end())
		return;
	for (auto listIt : it->second)
	{
		if (listIt == handler)
		{
			if (listIt != it->second.back())
			{
				it->second.remove(listIt);
				delete listIt;
			}
			break;
		}
	}
}

void EventManager::ClearEventHandler(EventKey id)
{
	m_events.erase(id);
}

void EventManager::DispatchEvent(EventKey key, EventData &data, EventSender * sender/*=nullptr*/)
{
	//printf("Begine\n");
	auto it = m_events.find(key);
	if (it == m_events.end())
	{
		printf("[Error]:EventManager::DispatchEvent()::It is the end, DispatchEvent can't find this<%u>event Handler\n", key);
		printf("End\n");
		return;
	}

	auto & handlerList = it->second;
	for (auto listIt : handlerList)
	{
		if (listIt != nullptr)
		{
			if (listIt->m_sender == sender)
			{
				listIt->DispatchEvent(key, data, sender);
			}
		}
	}
	//printf("End\n");
}

EventData &
EventManager::GetEventData(EventKey id)
{
	EventData * eventData;
	auto it = m_dataMaps.find(id);
	if (it == m_dataMaps.end())
	{
		printf("GetEventData:new eventData\n");
		eventData = new EventData();
		m_dataMaps[id] = eventData;
		return *eventData;
	}
	eventData = it->second;
	return *eventData;
}

EventKey
EventNameRegistrar::RegisterEventName(const char * eventName)
{
	EventKey id = Math::bkdrHash(eventName);
    GetEventNameMap()[id] = eventName;
    return id;
}

const std::string &
EventNameRegistrar::GetEventName(EventKey eventID)
{
	auto it = GetEventNameMap().find(eventID);
	std::shared_ptr<std::string> str = std::shared_ptr<std::string>(new std::string(""));
    return  it != GetEventNameMap().end() ? it->second : *str;
}

__gnu_cxx::hash_map<EventKey, std::string> &
EventNameRegistrar::GetEventNameMap()
{
	static __gnu_cxx::hash_map<EventKey, std::string> eventNameMap_;
	return eventNameMap_;
}
