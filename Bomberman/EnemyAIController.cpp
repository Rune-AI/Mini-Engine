#include "EnemyAIController.h"
#include "LevelComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

Bomberman::EnemyAIController::EnemyAIController(BearBones::Entity* object, BearBones::Entity* level)
	: ControllerComponent{ object, level }
{
}

void Bomberman::EnemyAIController::Update()
{
	ControllerComponent::Update();

	auto pos = m_pOwner->GetTransform()->GetWorldPosition();
	int currentIndex = m_pLevel->GetIndexAtPos(pos.x, pos.y);


	if (m_LastIndex != currentIndex || m_LastDirection == Direction::None)
	{
		Direction randomDirection = Direction(rand()%5);
		switch (m_Intelligence)
		{
		case Bomberman::Intelligence::Dumb:

			if (randomDirection == m_LastDirection)
			{
				randomDirection = Direction::None;
			}
			Move(randomDirection);

			//Move(rand() % 100 / 100, rand() % 100 / 100);
			break;
		case Bomberman::Intelligence::Smart:

			std::vector<BearBones::Entity*> players{};
			m_pLevel->GetPlayers(players);


			//get direction to player
			auto playerPos = players[0]->GetTransform()->GetWorldPosition();
			float xDiff = playerPos.x - pos.x;
			float yDiff = playerPos.y - pos.y;
			Direction Direction = Direction::None;
			if (abs(xDiff) > abs(yDiff))
			{
				if (xDiff > 0)
				{
					Direction = Direction::Right;
				}
				else
				{
					Direction = Direction::Left;
				}
			}
			else
			{
				if (yDiff > 0)
				{
					Direction = Direction::Down;
				}
				else
				{
					Direction = Direction::Up;
				}
			}

			Move(Direction);
			break;
		}
	}
	else
	{
		Move(m_LastDirection);
	}

	
	m_LastIndex = currentIndex;
}

void Bomberman::EnemyAIController::Render() const
{
}

void Bomberman::EnemyAIController::SetIntelligence(Intelligence intelligence)
{
	m_Intelligence = intelligence;
}
