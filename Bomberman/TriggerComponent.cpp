#include "TriggerComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

Bomberman::TriggerComponent::TriggerComponent(BearBones::Entity* object)
	: Component{ object }
{
}

void Bomberman::TriggerComponent::Update()
{
	// check if any observer is in range
	// if so, notify the observer
	for (auto obs : m_Observers)
	{
		auto obsPos = obs->GetTransform()->GetWorldPosition();
		auto thisPos = m_pOwner->GetTransform()->GetWorldPosition();
		auto distance = sqrt(pow(obsPos.x - thisPos.x, 2) + pow(obsPos.y - thisPos.y, 2));
		if (distance < triggerRange)
		{
			OnTouch(obs);
			break;
		}
	}
}

void Bomberman::TriggerComponent::Render() const
{
}

void Bomberman::TriggerComponent::AddObserver(BearBones::Entity* observer)
{
	m_Observers.push_back(observer);
}

void Bomberman::TriggerComponent::SetObservers(std::vector<BearBones::Entity*> observers)
{
	m_Observers = observers;
}
