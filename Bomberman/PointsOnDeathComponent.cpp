#include "PointsOnDeathComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "LevelComponent.h"
#include "TransformComponent.h"

Bomberman::PointsOnDeathComponent::PointsOnDeathComponent(BearBones::Entity* object, Bomberman::LevelComponent* level)
	: DestructableComponent{ object }
	, m_pLevel{ level }
{
}

void Bomberman::PointsOnDeathComponent::Update()
{
}

void Bomberman::PointsOnDeathComponent::Render() const
{
}

void Bomberman::PointsOnDeathComponent::OnNotify(int data)
{
	auto pos = m_pOwner->GetTransform()->GetWorldPosition();
	int otherIndex = m_pLevel->GetIndexAtPos(pos.x, pos.y);

	if (data == otherIndex)
	{
		// give points
		m_pOwner->SetActive(false);
	}

}
