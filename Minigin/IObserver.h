#ifndef OBSERVER_INTERFACE_H
#define OBSERVER_INTERFACE_H

namespace BearBones
{
	template<typename T, typename D>
	class IObserver
	{
	public:
		virtual void OnNotify(D data) = 0;
		virtual IObserver<T, D>* GetObserver() = 0;
	};
}
#endif //OBSERVER_INTERFACE_H