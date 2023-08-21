#include "DebugComponent.h"


#include "DebugComponent.h"
#include "InputManager.h"
#include "GameManager.h"
#include <iostream>
#include <ServiceLocator.h>
#include <SceneManager.h>

Bomberman::DebugComponent::DebugComponent(BearBones::Entity* object)
	: Component{ object }
{
	std::cout << "Press F1 to go to menu" << std::endl;
	std::cout << "Press M to mute" << std::endl;
}

void Bomberman::DebugComponent::Update()
{
	if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_M))
	{
		BearBones::ServiceLocator::GetSoundService()->PauzeSimple();
	}

	if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_F1))
	{
		auto activeStream = BearBones::SceneManager::GetInstance().GetScene("Menu");
		if (activeStream)
		{
			if (activeStream->GetIsActive())
			{
				return;
			}
		}
		Bomberman::GameManager::GetInstance().UnloadGame();
		Bomberman::GameManager::GetInstance().LoadOptions();
	}
	
}

void Bomberman::DebugComponent::Render() const
{
}
