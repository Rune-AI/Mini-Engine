#include "BombComponent.h"
#include <EngineTime.h>
#include "LevelComponent.h"
#include <Entity.h>
#include "TransformComponent.h"
#include "ExplosionComponent.h"
#include <SpriteComponent.h>
#include <SceneManager.h>
#include <Scene.h>


Bomberman::BombComponent::BombComponent(BearBones::Entity* object, LevelComponent* level, int range)
	: DestructableComponent{ object }
	, m_pLevel{ level }
	, m_Range{ range }
{

}
void Bomberman::BombComponent::Update()
{
	m_BombTime += BearBones::TIME.GetDeltaTime();
	if (m_BombTime >= m_FuseTime)
	{
		Explode();
	}
}

void Bomberman::BombComponent::Render() const
{
}

void Bomberman::BombComponent::OnNotify(int index)
{
	auto pos = m_pOwner->GetTransform()->GetWorldPosition();
	int otherIndex = m_pLevel->GetIndexAtPos(pos.x, pos.y);

	if (index == otherIndex)
	{
		if (!m_IsExploding)
		{
			Explode();
		}
	}
}

void Bomberman::BombComponent::Explode()
{
	if (m_IsExploding)
	{
		return;
	}
	m_IsExploding = true;
	auto pos = m_pOwner->GetTransform()->GetWorldPosition();

	int index = m_pLevel->GetIndexAtPos(pos.x, pos.y);
	m_pLevel->SetGroundStateAtPos(pos.x, pos.y, GroundState::Empty);
	NotifyObservers(index);
	SpawnExplosion(pos.x, pos.y);
	

	for (int i = 0; i < m_Range; i++)
	{
		pos.x += m_pLevel->GetTileSize();
		if (CheckForWall(pos.x, pos.y))
		{
			break;
		}
	}
	pos = m_pOwner->GetTransform()->GetWorldPosition();
	for (int i = 0; i < m_Range; i++)
	{
		pos.x -= m_pLevel->GetTileSize();
		if (CheckForWall(pos.x, pos.y))
		{
			break;
		}
	}
	pos = m_pOwner->GetTransform()->GetWorldPosition();
	for (int i = 0; i < m_Range; i++)
	{
		pos.y += m_pLevel->GetTileSize();
		if (CheckForWall(pos.x, pos.y))
		{
			break;
		}
	}
	pos = m_pOwner->GetTransform()->GetWorldPosition();
	for (int i = 0; i < m_Range; i++)
	{
		pos.y -= m_pLevel->GetTileSize();
		if (CheckForWall(pos.x, pos.y))
		{
			break;
		}
	}

	m_pOwner->SetActive(false);
}

void Bomberman::BombComponent::SpawnExplosion(float /*x*/, float /*y*/)
{
	/*auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");

	auto explosion = std::make_unique<BearBones::Entity>();
	explosion->AddComponent<ExplosionComponent>();
	explosion->GetTransform()->SetWorldPosition(x, y);

	scene->Add(std::move(explosion));*/
}

bool Bomberman::BombComponent::CheckForWall(float x, float y)
{
	auto groundState = m_pLevel->GetGroundStateAtPos(x, y);

	if (groundState == GroundState::Solid)
	{
		return true;
	}

	SpawnExplosion(x, y);

	if (groundState == GroundState::Wall || groundState == GroundState::Bomb)
	{
		// singal wall to be destroyed
		NotifyObservers(m_pLevel->GetIndexAtPos(x, y));

		// Set ground state to empty
		m_pLevel->SetGroundStateAtPos(x, y, GroundState::Empty);
		return true;
	}

	return false;
}
