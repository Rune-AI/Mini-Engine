#include "ExplosionComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"

Bomberman::ExplosionComponent::ExplosionComponent(BearBones::Entity* object)
	: Component{ object }
{
	object->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/GeneralSprites.png");
	object->SetZOrder(5);


	auto  sprite = m_pOwner->GetComponent<BearBones::SpriteComponent>();
	sprite->SetSpriteIndexStart(90);
	sprite->SetSpriteIndexEnd(98);
	sprite->SetIsLooping(false);
	sprite->SetIsPlaying(false);
}

void Bomberman::ExplosionComponent::Update()
{
}

void Bomberman::ExplosionComponent::Render() const
{
}
