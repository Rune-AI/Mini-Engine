#ifndef SUBJECT_H
#define SUBJECT_H

#include "IObserver.h"
#include <vector>

namespace BearBones
{

	template<typename T, typename D>
	class Subject
	{
	public:
		void RegisterObserver(IObserver<T, D>* observer)
		{
			m_Observers.push_back(observer);
		}

		void RemoveObserver(IObserver<T, D>* observer)
		{
			m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
		}

		void NotifyObservers(D data)
		{
			for (auto observer : m_Observers)
			{
				observer->OnNotify(data);
			}
		}

	protected:
		std::vector<IObserver<T, D>*> m_Observers;
	};
}

#endif //SUBJECT_H