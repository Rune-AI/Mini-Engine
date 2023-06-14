#ifndef OBSERVER_INTERFACE_H
#define OBSERVER_INTERFACE_H

namespace BearBones
{
	template<typename T>
	class IObserver
	{
	public:
		virtual void OnNotify(T data) = 0;
		virtual IObserver<T>* GetObserver() = 0;
	};
}
#endif //OBSERVER_INTERFACE_H