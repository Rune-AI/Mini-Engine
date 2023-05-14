#pragma once
#include "Singleton.h"

class Time final : public Singleton<Time>
{
public:
	void Update(float deltaTime);

	float GetDeltaTime() const;
	double GetElapsedTime() const;

private:
	float m_DeltaTime{};
	double m_ElapsedTime{};
};

