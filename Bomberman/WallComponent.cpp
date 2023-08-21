#include "WallComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "LevelComponent.h"
#include "TransformComponent.h"

Bomberman::WallComponent::WallComponent(BearBones::Entity* object, Bomberman::LevelComponent* level)
	: DestructableComponent{ object }
	, m_pLevel{ level }
{
	object->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/Block.png");
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexStart(0);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteIndexEnd(6);
	object->GetComponent<BearBones::SpriteComponent>()->SetSpriteTimePerFrame(1);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsLooping(true);
	object->GetComponent<BearBones::SpriteComponent>()->SetIsPlaying(false);

	object->SetZOrder(1);
}

void Bomberman::WallComponent::Update()
{
}

void Bomberman::WallComponent::Render() const
{
}

void Bomberman::WallComponent::OnNotify(int data)
{
	auto pos = m_pOwner->GetTransform()->GetWorldPosition();
	int otherIndex = m_pLevel->GetIndexAtPos(pos.x, pos.y);

	if (data == otherIndex)
	{
		// give points/spawn door/powerups
		m_pOwner->SetActive(false);
	}
	
}
