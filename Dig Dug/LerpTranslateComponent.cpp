#include "LerpTranslateComponent.h"
#include <EngineTime.h>
#include <Entity.h>
#include <TransformComponent.h>


DigDug::LerpTranslateComponent::LerpTranslateComponent(BearBones::Entity* object, float destinationX, float destinationY, float lerpTime)
	: Component{ object }
	, m_destinationPos { destinationX, destinationY }
	, m_lerpTime{ lerpTime }
{
	m_originalPos = m_pOwner->GetTransform()->GetLocalPosition();
}

void DigDug::LerpTranslateComponent::Update()
{
	m_currentTime += BearBones::TIME.GetDeltaTime();
	float t = m_currentTime / m_lerpTime;
	if (t > 1.f) return;
	float x = m_originalPos.x + (m_destinationPos.x - m_originalPos.x) * t;
	float y = m_originalPos.y + (m_destinationPos.y - m_originalPos.y) * t;
	m_pOwner->GetTransform()->SetLocalPosition(x, y);
}