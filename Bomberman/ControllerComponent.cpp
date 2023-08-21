#include "ControllerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelComponent.h"
#include "TransformComponent.h"
#include <EngineTime.h>
#include <iostream>

Bomberman::ControllerComponent::ControllerComponent(BearBones::Entity* object, BearBones::Entity* level)
	: Component{ object },
	m_pLevel{ level->GetComponent<LevelComponent>() }
{
}

void Bomberman::ControllerComponent::Update()
{
}

void Bomberman::ControllerComponent::Render() const
{
}

void Bomberman::ControllerComponent::Move(float x, float y)
{
	Direction direction{Direction::None};
	if (x > 0.f && abs(x) > abs(y))
	{
		direction = Direction::Right;
	}
	else if (x < 0.f && abs(x) > abs(y))
	{
		direction = Direction::Left;
	}
	else if (y > 0.f && abs(y) > abs(x))
	{
		direction = Direction::Up;
	}
	else if (y < 0.f && abs(y) > abs(x))
	{
		direction = Direction::Down;
	}
	
	Move(direction);
}

void Bomberman::ControllerComponent::Move(Direction direction)
{
	auto pos = m_pOwner->GetTransform()->GetWorldPosition();

	auto checkCollisionPos = pos;
	float halfColSize = m_CollisionSize / 2.f;
	checkCollisionPos.x += halfColSize;
	checkCollisionPos.y += halfColSize;

	auto currentGroundState = m_pLevel->GetGroundStateAtPos(checkCollisionPos.x, checkCollisionPos.y);

	switch (direction)
	{
	case Bomberman::Direction::Up:
		checkCollisionPos.y += halfColSize;
		break;
	case Bomberman::Direction::Down:
		checkCollisionPos.y -= halfColSize;
		break;
	case Bomberman::Direction::Left:
		checkCollisionPos.x += halfColSize;
		break;
	case Bomberman::Direction::Right:
		checkCollisionPos.x -= halfColSize;
		break;
	default:
		break;
	}

	int index = m_pLevel->GetIndexAtPos(checkCollisionPos.x, checkCollisionPos.y);


	m_LastDirection = direction;
	GroundState nextGroundState = GroundState::Empty;
	int nextIndex = -1;
	switch (direction)
	{
	case Bomberman::Direction::Up:
		nextIndex = index - m_pLevel->GetLevelSizeX();
		nextGroundState = m_pLevel->GetGroundStateAtIndex(nextIndex);
		if (nextGroundState == GroundState::Empty || (currentGroundState == GroundState::Bomb && nextGroundState == GroundState::Bomb))
		{
			pos.y -= m_Speed * BearBones::TIME.GetDeltaTime();
			m_pOwner->GetTransform()->SetWorldPosition(pos);
		}
		break;
	case Bomberman::Direction::Down:
		nextIndex = index + m_pLevel->GetLevelSizeX();
		nextGroundState = m_pLevel->GetGroundStateAtIndex(nextIndex);
		if (nextGroundState == GroundState::Empty || (currentGroundState == GroundState::Bomb && nextGroundState == GroundState::Bomb))
		{
			pos.y += m_Speed * BearBones::TIME.GetDeltaTime();
			m_pOwner->GetTransform()->SetWorldPosition(pos);
		}
		break;
	case Bomberman::Direction::Left:
		nextIndex = index - 1;
		nextGroundState = m_pLevel->GetGroundStateAtIndex(nextIndex);
		if (nextGroundState == GroundState::Empty || (currentGroundState == GroundState::Bomb && nextGroundState == GroundState::Bomb))
		{
			pos.x -= m_Speed * BearBones::TIME.GetDeltaTime();
			m_pOwner->GetTransform()->SetWorldPosition(pos);
		}
		break;
	case Bomberman::Direction::Right:
		nextIndex = index + 1;
		nextGroundState = m_pLevel->GetGroundStateAtIndex(nextIndex);
		if (nextGroundState == GroundState::Empty || (currentGroundState == GroundState::Bomb && nextGroundState == GroundState::Bomb))
		{
			pos.x += m_Speed * BearBones::TIME.GetDeltaTime();
			m_pOwner->GetTransform()->SetWorldPosition(pos);
		}
		break;
	default:
		break;
	}



	auto nextPos = m_pLevel->GetPosAtIndex(nextIndex);

	//glichy
	if (nextGroundState != GroundState::Empty && nextGroundState != GroundState::Bomb)
	{
		switch (direction)
		{

		case Bomberman::Direction::Up:
			pos.y -= (pos.y - nextPos.y) - m_CollisionSize;
			/*pos.y = std::round(pos.y);
			pos.y += int(pos.y) % int(m_CollisionSize);*/
			m_pOwner->GetTransform()->SetWorldPosition(pos);
			break;
		case Bomberman::Direction::Down:
			pos.y -= (pos.y - nextPos.y) + m_CollisionSize;
			/*pos.y = std::round(pos.y);
			pos.y -= int(pos.y) % int(m_CollisionSize);*/
			m_pOwner->GetTransform()->SetWorldPosition(pos);
			break;
		case Bomberman::Direction::Left:
			pos.x -= (pos.x - nextPos.x) - m_CollisionSize;
			/*pos.x = std::round(pos.x);
			pos.x += int(pos.x) % int(m_CollisionSize);*/
			m_pOwner->GetTransform()->SetWorldPosition(pos);
			break;
		case Bomberman::Direction::Right:
			pos.x -= (pos.x - nextPos.x) + m_CollisionSize;
			/*pos.x = std::round(pos.x);
			pos.x -= int(pos.x) % int(m_CollisionSize);*/
			m_pOwner->GetTransform()->SetWorldPosition(pos);
			break;
		default:
			break;
		}
		
		m_LastDirection = Direction::None;
	}
}

Bomberman::Direction Bomberman::ControllerComponent::GetDirection() const
{
	return m_LastDirection;
}

void Bomberman::ControllerComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}
