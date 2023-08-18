#include "LevelComponent.h"

#include <Entity.h>
#include <Scene.h>
#include "WallComponent.h"
#include "TransformComponent.h"

Bomberman::LevelComponent::LevelComponent(BearBones::Entity* object, int sizeX, int sizeY)
	: Component{ object }
	, m_gridSize{ sizeX, sizeY }
{
	//generate grid
	for (int i = 0; i < m_gridSize.x * m_gridSize.y; i++)
	{
		if (i == m_gridSize.x + 1 || i == m_gridSize.x + 2 || i == m_gridSize.x * 2 + 1)
		{
			m_groundStates.emplace_back(0);
		}
		else if (i < m_gridSize.x)
		{
			m_groundStates.emplace_back(1);
		}
		else if (i > m_gridSize.x * m_gridSize.y - m_gridSize.x)
		{
			m_groundStates.emplace_back(1);
		}
		else if (i % m_gridSize.x == 0 || i % m_gridSize.x == m_gridSize.x - 1)
		{
			m_groundStates.emplace_back(1);
		}
		else if (i % 2 == 0 && i / m_gridSize.x % 2 == 0)
		{
			m_groundStates.emplace_back(1);
		}
		else
		{
			int blockChance = 50;
			int probabilityrand = rand()%100;
			if (probabilityrand > blockChance)
			{
				m_groundStates.emplace_back(0);
			}
			else
			{
				m_groundStates.emplace_back(2);
			}
		}
	}


	auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");

	//generate blocks
	for (int i = 0; i < m_gridSize.x * m_gridSize.y; i++)
	{
		if (m_groundStates[i] == 2)
		{
			//spawn block
			auto block = std::make_unique<BearBones::Entity>();
			block->AddComponent<WallComponent>();
			block->GetTransform()->SetLocalPosition((i % m_gridSize.x) * 16.f, (i / m_gridSize.x) * 16.f);
			scene->Add(std::move(block));
		}
	}

	//generate 
}

void Bomberman::LevelComponent::Update()
{
}

void Bomberman::LevelComponent::Render() const
{
}
