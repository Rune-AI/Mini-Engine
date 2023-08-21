#include "PlayerController.h"

#include "LevelComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "BombCommand.h"
#include "EngineTime.h"
#include <iostream>

Bomberman::PlayerController::PlayerController(BearBones::Entity* object, BearBones::Entity* level)
	: ControllerComponent{ object, level }
	, m_BombCommand{ object, level->GetComponent<LevelComponent>() }

{
	BearBones::InputManager::GetInstance().CreateController(0);
}

Bomberman::PlayerController::PlayerController(BearBones::Entity* object, BearBones::Entity* level, bool m_UseArrows, bool m_useWASD, bool m_UseController)
	: ControllerComponent{ object, level }
	, m_UseArrows{ m_UseArrows }
	, m_UseWASD{ m_useWASD }
	, m_UseController{ m_UseController }
	, m_BombCommand{ object, level->GetComponent<LevelComponent>()}
{
	BearBones::InputManager::GetInstance().CreateController(0);
}

void Bomberman::PlayerController::Update()
{
	m_BombSpawnTime += BearBones::TIME.GetDeltaTime();
	if (m_BombSpawnTime > m_BombSpawnDelay / m_BombCount)
	{
		//std::cout << "Add bomb" << std::endl;
		m_BombSpawnTime -= m_BombSpawnDelay / m_BombCount;
		++m_CurrentBombCount;
 		m_CurrentBombCount = std::min(m_CurrentBombCount, m_BombCount);
	}

	HandleInput();
	ControllerComponent::Update();
}

void Bomberman::PlayerController::HandleInput()
{
	auto keyboardDirection = glm::vec2{};
	if (m_UseWASD)
	{
		keyboardDirection +=
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_D) ? glm::vec2{ 1, 0 } :
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_A) ? glm::vec2{ -1, 0 } :
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_S) ? glm::vec2{ 0, -1 } :
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_W) ? glm::vec2{ 0, 1 } :
			glm::vec2{};

		if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_SPACE))
		{

			SpawnBomb();
		}
	}

	if (m_UseArrows)
	{
		keyboardDirection +=
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_RIGHT) ? glm::vec2{ 1, 0 } :
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_LEFT) ? glm::vec2{ -1, 0 } :
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_DOWN) ? glm::vec2{ 0, -1 } :
			BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_UP) ? glm::vec2{ 0, 1 } :
			glm::vec2{};

		if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_RETURN))
		{

			SpawnBomb();
		}
	}


	auto controllerDirection = glm::vec2{};
	if (m_UseController)
	{
		controllerDirection +=
			BearBones::InputManager::GetInstance().GetController()->IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT) ? glm::vec2{ 1, 0 } :
			BearBones::InputManager::GetInstance().GetController()->IsPressed(XINPUT_GAMEPAD_DPAD_LEFT) ? glm::vec2{ -1, 0 } :
			BearBones::InputManager::GetInstance().GetController()->IsPressed(XINPUT_GAMEPAD_DPAD_UP) ? glm::vec2{ 0, -1 } :
			BearBones::InputManager::GetInstance().GetController()->IsPressed(XINPUT_GAMEPAD_DPAD_DOWN) ? glm::vec2{ 0, 1 } :
			glm::vec2{};



		controllerDirection += BearBones::InputManager::GetInstance().GetController()->GetLeftThumbStick();
		controllerDirection.y = -controllerDirection.y;

		if (BearBones::InputManager::GetInstance().GetController()->IsPressed(XINPUT_GAMEPAD_A))
		{

			SpawnBomb();
		}
	}

	

	

	auto direction = keyboardDirection + controllerDirection;



	Move(direction.x, direction.y);


}

void Bomberman::PlayerController::SpawnBomb()
{
	if (m_CurrentBombCount > 0)
	{
		--m_CurrentBombCount;
		m_BombCommand.Execute();
	}
}

void Bomberman::PlayerController::Render() const
{
}

void Bomberman::PlayerController::IncrementFlamePower()
{
	++m_FlamePower;
}

void Bomberman::PlayerController::IncrementBombCount()
{
	++m_BombCount;
}

int Bomberman::PlayerController::GetFlamePower() const
{
	return m_FlamePower;
}

int Bomberman::PlayerController::GetBombCount() const
{
	return m_BombCount;
}

void Bomberman::PlayerController::KillPlayer()
{
	m_IsDead = true;

}

bool Bomberman::PlayerController::IsDead() const
{
	return m_IsDead;
}

void Bomberman::PlayerController::SetUseArrows(bool useArrows)
{
	m_UseArrows = useArrows;
}

void Bomberman::PlayerController::SetUseWASD(bool useWASD)
{
	m_UseWASD = useWASD;
}

void Bomberman::PlayerController::SetUseController(bool useController)
{
	m_UseController = useController;
}