#include "EventManager.h"

void EventManager::AttachEvent(const std::string& name, std::function<void(Event*)> pEvent)
{
	m_Events.insert_or_assign(name.c_str(), pEvent);
}

void EventManager::DetachEvent(const std::string& name)
{
	m_Events.erase(name.c_str());
}

void EventManager::Notify(const std::string& name, Event* pEvent)
{
	if (m_Events.contains(name.c_str()))
	{
		m_Events[name.c_str()](pEvent);
	}
}