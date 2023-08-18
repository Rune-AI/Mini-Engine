#include "WallComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"

Bomberman::WallComponent::WallComponent(BearBones::Entity* object)
	: DestructableComponent{ object }
{
	object->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/Block.png");
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexStart(0);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexEnd(6);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteTimePerFrame(1);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsLooping(true);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsPlaying(true);
}

void Bomberman::WallComponent::Update()
{
}

void Bomberman::WallComponent::Render() const
{
}

void Bomberman::WallComponent::OnDestroy()
{


}
