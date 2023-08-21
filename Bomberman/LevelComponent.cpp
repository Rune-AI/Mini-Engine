#include "LevelComponent.h"

#include <Entity.h>
#include <Scene.h>
#include "WallComponent.h"
#include "TransformComponent.h"
#include "IObserver.h"
#include "DoorComponent.h"
#include "EntityFactory.h"
#include "TriggerComponent.h"
#include "FlamePowerpupComponent.h"
#include "GameManager.h"
#include "PlayerController.h"

Bomberman::LevelComponent::LevelComponent(BearBones::Entity* object, int sizeX, int sizeY)
	: Component{ object }
	, m_gridSize{ sizeX, sizeY }
{
	//generate grid
	for (int i = 0; i < m_gridSize.x * m_gridSize.y; i++)
	{
		if (i == m_gridSize.x + 1 || i == m_gridSize.x + 2 || i == m_gridSize.x * 2 + 1)
		{
			m_groundStates.emplace_back(GroundState::Empty);
		}
		else if (i < m_gridSize.x)
		{
			m_groundStates.emplace_back(GroundState::Solid);
		}
		else if (i > m_gridSize.x * m_gridSize.y - m_gridSize.x)
		{
			m_groundStates.emplace_back(GroundState::Solid);
		}
		else if (i % m_gridSize.x == 0 || i % m_gridSize.x == m_gridSize.x - 1)
		{
			m_groundStates.emplace_back(GroundState::Solid);
		}
		else if (i % 2 == 0 && i / m_gridSize.x % 2 == 0)
		{
			m_groundStates.emplace_back(GroundState::Solid);
		}
		else
		{
			int blockChance = 30;
			int probabilityrand = rand()%100;
			if (probabilityrand > blockChance)
			{
				m_groundStates.emplace_back(GroundState::Empty);
			}
			else
			{
				m_groundStates.emplace_back(GroundState::Wall);
			}
		}
	}


	auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");
	Bomberman::EntityFactory entityFactory{};


	std::vector<int> freeWalls{};
	//generate blocks
	for (int i = 0; i < m_gridSize.x * m_gridSize.y; i++)
	{
		if (m_groundStates[i] == GroundState::Wall)
		{
			//spawn block
			auto block = std::make_unique<BearBones::Entity>();
			block->AddComponent<WallComponent>(this);
			m_Destructibles.push_back(block->GetComponent<WallComponent>());

			block->GetTransform()->SetLocalPosition(float((i % m_gridSize.x) * m_TileSize), float((i / m_gridSize.x) * m_TileSize));
			scene->Add(std::move(block));

			//spawn powerup chance
			int powerupChance = 20;
			int probabilityrand = rand() % 100;
			if (probabilityrand < powerupChance)
			{
				//spawn powerup
				std::unique_ptr<BearBones::Entity> powerup;
				if (rand() % 2 == 0)
				{
					powerup = entityFactory.CreateFlamePowerup();
				}
				else
				{
					powerup = entityFactory.CreateExtraBombPowerup();
				}
				
				powerup->GetTransform()->SetLocalPosition(float((i % m_gridSize.x) * m_TileSize), float((i / m_gridSize.x) * m_TileSize));

				auto trigger = powerup->GetComponent<TriggerComponent>();
				m_Triggers.push_back(trigger);

				scene->Add(std::move(powerup));
			}
			else
			{
				freeWalls.push_back(i);
			}
		}
	}



	//spawn door
	int randomWallIndex = rand() % freeWalls.size();
	randomWallIndex = freeWalls[randomWallIndex];
	auto door = entityFactory.CreateDoor(m_pOwner);
	door->GetTransform()->SetLocalPosition(float((randomWallIndex % m_gridSize.x) * m_TileSize), float((randomWallIndex / m_gridSize.x) * m_TileSize));
	m_Triggers.push_back(door->GetComponent<TriggerComponent>());
	scene->Add(std::move(door));
}

void Bomberman::LevelComponent::Update()
{
	CheckGameOver();
}

void Bomberman::LevelComponent::Render() const
{
}

int Bomberman::LevelComponent::GetIndexAtPos(float x, float y) const
{
	int posX = int(x / m_TileSize);
	int posY = int(y / m_TileSize);
	return posY * m_gridSize.x + posX;
}

Bomberman::GroundState Bomberman::LevelComponent::GetGroundStateAtPos(float x, float y) const
{
	return GetGroundStateAtIndex(GetIndexAtPos(x, y));

}

Bomberman::GroundState Bomberman::LevelComponent::GetGroundStateAtIndex(int index) const
{
	index < 0 ? index = 0 : index;
	index > int(m_groundStates.size()) - 1 ? index = int(m_groundStates.size()) - 1 : index;
	return m_groundStates[index];
}

void Bomberman::LevelComponent::SetGroundStateAtPos(float x, float y, GroundState state)
{
	SetGroundStateAtIndex(GetIndexAtPos(x, y), state);
}

void Bomberman::LevelComponent::SetGroundStateAtIndex(int index, GroundState state)
{
	index < 0 ? index = 0 : index;
	index > int(m_groundStates.size()) - 1 ? index = int(m_groundStates.size()) - 1 : index;
	m_groundStates[index] = state;
}

int Bomberman::LevelComponent::GetLevelSizeX() const
{
	return m_gridSize.x;
}

int Bomberman::LevelComponent::GetLevelSizeY() const
{
	return m_gridSize.y;
}

int Bomberman::LevelComponent::GetTileSize() const
{
	return m_TileSize;
}

glm::vec2 Bomberman::LevelComponent::GetPosAtIndex(int index) const
{
	return glm::vec2(index % m_gridSize.x * m_TileSize, index / m_gridSize.x * m_TileSize);
}

void Bomberman::LevelComponent::ExplodeAtPos(float x, float y)
{
	int index = GetIndexAtPos(x, y);
	if (GetGroundStateAtIndex(index) == GroundState::Wall)
	{
		SetGroundStateAtIndex(index, GroundState::Empty);
	}
}

std::vector<Bomberman::DestructableComponent*> Bomberman::LevelComponent::GetDestructibles() const
{
	return m_Destructibles;
}

void Bomberman::LevelComponent::AddDestructible(DestructableComponent* destructible)
{
	m_Destructibles.push_back(destructible);
}

void Bomberman::LevelComponent::AddPlayer(BearBones::Entity* player)
{
	m_Players.push_back(player);
	for (auto var : m_Triggers)
	{
		var->AddObserver(player);
	}
}

void Bomberman::LevelComponent::GetPlayers(std::vector<BearBones::Entity*>& players) const
{
	players = m_Players;
}

void Bomberman::LevelComponent::GetEnemies(std::vector<BearBones::Entity*>& enemies) const
{
	enemies = m_Enemies;
}

void Bomberman::LevelComponent::SpawnEnemies()
{
	
	for (int i = 0; i < m_gridSize.x * m_gridSize.y; i++)
	{
		if (i == m_gridSize.x + 1 || i == m_gridSize.x + 2 || i == m_gridSize.x * 2 + 1)
		{
			continue;
		}

		if (m_groundStates[i] == GroundState::Empty)
		{
			//Spawn enemy chance
			int probabilityrand = rand() % 100;
			if (probabilityrand < m_EnemySpawnChance)
			{
				//spawn enemy
				SpawnRandomEnemy(i);
			}
		}
	}

}

void Bomberman::LevelComponent::SetTriggers()
{

	for (auto var : m_Triggers)
	{
		auto observers = m_Players;
		observers.insert(observers.end(), m_Enemies.begin(), m_Enemies.end());
		var->SetObservers(observers);
	}
}

void Bomberman::LevelComponent::CheckGameOver()
{
	for (auto player : m_Players)
	{
		if (player->GetComponent<PlayerController>()->IsDead())
		{
			GameManager::GetInstance().ResetGame();
		}
	}
}

void Bomberman::LevelComponent::SpawnRandomEnemy(int index)
{
	Bomberman::EntityFactory entityFactory{};


	auto random = rand() % 4;
	std::unique_ptr<BearBones::Entity> enemy;
	switch (random)
	{
	case 0:
		enemy = entityFactory.CreateBalloom(m_pOwner);
		break;
	case 1:
		enemy = entityFactory.CreateOneal(m_pOwner);
		break;
	case 2:
		enemy = entityFactory.CreateDoll(m_pOwner);
		break;
	case 3:
		enemy = entityFactory.CreateMinvo(m_pOwner);
	}

	enemy->GetTransform()->SetWorldPosition(float((index % m_gridSize.x) * m_TileSize), float((index / m_gridSize.x) * m_TileSize));
	auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");
	m_Enemies.push_back(enemy.get());
	m_Triggers.push_back(enemy->GetComponent<TriggerComponent>());

	scene->Add(std::move(enemy));

}


