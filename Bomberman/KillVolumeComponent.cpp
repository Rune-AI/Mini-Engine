#include "KillVolumeComponent.h"
#include "Entity.h"
#include "PlayerController.h"
#include <iostream>

Bomberman::KillVolumeComponent::KillVolumeComponent(BearBones::Entity* object, BearBones::Entity* Level)
	: TriggerComponent{ object }
	, m_pLevel{ Level->GetComponent<LevelComponent>() }
{
}
void Bomberman::KillVolumeComponent::Update()
{
	TriggerComponent::Update();
}
void Bomberman::KillVolumeComponent::Render() const
{
}
void Bomberman::KillVolumeComponent::OnTouch(BearBones::Entity* other)
{
	if (other->HasComponent<Bomberman::ControllerComponent>())
	{
		other->SetActive(false);
		std::cout << "DEATH" << std::endl;

	}
}

