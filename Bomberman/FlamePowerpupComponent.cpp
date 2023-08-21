#include "FlamePowerpupComponent.h"
#include "Entity.h"
#include "PlayerController.h"
#include <iostream>
#include <SpriteComponent.h>


Bomberman::FlamePowerpupComponent::FlamePowerpupComponent(BearBones::Entity* object)
	: TriggerComponent{ object }
{
	object->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/GeneralSprites.png");
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexStart(197);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexEnd(198);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteTimePerFrame(1);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsLooping(false);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsPlaying(false);

}
void Bomberman::FlamePowerpupComponent::Update()
{
	TriggerComponent::Update();
}
void Bomberman::FlamePowerpupComponent::Render() const
{
}
void Bomberman::FlamePowerpupComponent::OnTouch(BearBones::Entity* other)
{
	if (other->HasComponent<Bomberman::PlayerController>())
	{
		other->GetComponent<PlayerController>()->IncrementFlamePower();
		std::cout << "Flame On" << std::endl;
		m_pOwner->SetActive(false);
	}

}

