#include "Time.h"

void Time::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

double Time::GetElapsedTime() const
{
	return m_ElapsedTime;
}
