#pragma once
#include "IObserver.h"
#include <vector>

template<typename T>
class Subject
{
public:
	void RegisterObserver(IObserver<T>* observer)
	{
		m_Observers.push_back(observer);
	}

	void RemoveObserver(IObserver<T>* observer)
	{
		m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
	}

	void NotifyObservers(T data)
	{
		for (auto observer : m_Observers)
		{
			observer->OnNotify(data);
		}
	}

private:
	std::vector<IObserver<T>*> m_Observers;
};