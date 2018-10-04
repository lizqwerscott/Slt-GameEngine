#include "EventManager.h"
#include "Event.h"
#include "EventHandler.h"
#include "EventSender.h"
#include "EventReciver.h"

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
}

void EventManager::AddEventHandler(int id, EventHandler * handler)
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

void EventManager::RemoveEventHandler(int id, EventHandler * handler)
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

void EventManager::ClearEventHandler(int id)
{
	m_events.erase(id);
}

void EventManager::DispatchEvent(Event * evt, EventSender * sender/*=nullptr*/)
{
	printf("Begine\n");
	auto it = m_events.find(evt->getEventKey());
	if (it == m_events.end())
	{
		printf("[Error]:EventManager::DispatchEvent()::It is the end, DispatchEvent can't find this<%d>event Handler\n", evt->getEventKey());
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
				listIt->DispatchEvent(evt, sender);
			}
		}
	}
	printf("End\n");
	delete evt;
}

