#pragma once

template<typename T>
class IObserver
{
public:
	virtual void OnNotify(T data) = 0;
	virtual IObserver<T>* GetObserver() = 0;
};
