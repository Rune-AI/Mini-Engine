#include "KillPlayerVolumeComponent.h"
#include "Entity.h"
#include "PlayerController.h"
#include <iostream>

Bomberman::KillPlayerVolumeComponent::KillPlayerVolumeComponent(BearBones::Entity* object, BearBones::Entity* Level)
	: TriggerComponent{ object }
	, m_pLevel{ Level->GetComponent<LevelComponent>() }
{
}
void Bomberman::KillPlayerVolumeComponent::Update()
{
	TriggerComponent::Update();
}
void Bomberman::KillPlayerVolumeComponent::Render() const
{
}
void Bomberman::KillPlayerVolumeComponent::OnTouch(BearBones::Entity* other)
{
	if (other->HasComponent<Bomberman::PlayerController>())
	{
		other->GetComponent<PlayerController>()->KillPlayer();
		std::cout << "PLAYER DEATH" << std::endl;

	}
}

