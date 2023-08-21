#include "ExtraBombComponent.h"
#include "Entity.h"
#include "PlayerController.h"
#include <iostream>
#include <SpriteComponent.h>


Bomberman::ExtraBombComponent::ExtraBombComponent(BearBones::Entity* object)
	: TriggerComponent{ object }
{
	object->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/GeneralSprites.png");
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexStart(196);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexEnd(197);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteTimePerFrame(1);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsLooping(false);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsPlaying(false);

}
void Bomberman::ExtraBombComponent::Update()
{
	TriggerComponent::Update();
}
void Bomberman::ExtraBombComponent::Render() const
{
}
void Bomberman::ExtraBombComponent::OnTouch(BearBones::Entity* other)
{
	if (other->HasComponent<Bomberman::PlayerController>())
	{
		other->GetComponent<PlayerController>()->IncrementBombCount();
		std::cout << "Extra bomb" << std::endl;
		m_pOwner->SetActive(false);
	}

}

