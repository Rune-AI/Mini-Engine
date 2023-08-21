#include "BombCommand.h"
#include <memory>
#include <Entity.h>
#include "BombComponent.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include <SpriteComponent.h>
#include "PlayerController.h"

Bomberman::BombCommand::BombCommand(BearBones::Entity* player, Bomberman::LevelComponent* level)
	: Command{ player }
	, m_pLevel{ level }
{
}

void Bomberman::BombCommand::Execute()
{
	auto playerCont = m_Entity->GetComponent<Bomberman::PlayerController>();



	auto pos = m_Entity->GetTransform()->GetWorldPosition();
	pos.x += 8;
	pos.y += 8;


	auto bomb = std::make_unique<BearBones::Entity>();


	
	bomb->AddComponent<Bomberman::BombComponent>(m_pLevel, playerCont->GetFlamePower());
	bomb->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/GeneralSprites.png");
	bomb->SetZOrder(1);
	

	auto  sprite = bomb->GetComponent<BearBones::SpriteComponent>();
	sprite->SetSpriteIndexStart(42);
	sprite->SetSpriteIndexEnd(45);
	sprite->SetIsLooping(true);
	sprite->SetIsPlaying(true);


	auto alignedPos = m_pLevel->GetPosAtIndex(m_pLevel->GetIndexAtPos(pos.x, pos.y));
	bomb->GetTransform()->SetLocalPosition(alignedPos.x, alignedPos.y);       

	m_pLevel->SetGroundStateAtPos(pos.x, pos.y, GroundState::Bomb);

	auto destructibles = m_pLevel->GetDestructibles();
	for (size_t i = 0; i < destructibles.size(); i++)
	{
		bomb->GetComponent<Bomberman::BombComponent>()->RegisterObserver(destructibles[i]);
	}

	m_pLevel->AddDestructible(bomb->GetComponent<Bomberman::BombComponent>());

	auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");
	scene->Add(std::move(bomb));
}
