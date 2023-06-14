#include "EngineTime.h"

void BearBones::Time::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
}

float BearBones::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

double BearBones::Time::GetElapsedTime() const
{
	return m_ElapsedTime;
}
