#include "MenuComponent.h"
#include "InputManager.h"
#include "GameManager.h"
#include <iostream>

Bomberman::MenuComponent::MenuComponent(BearBones::Entity* object)
	: Component{ object }
{
	std::cout << "Press ENTER to start the game" << std::endl;
	std::cout << "Press 1 for SOLO" << std::endl;
	std::cout << "Press 2 for COOP" << std::endl;
	std::cout << "Press 3 for VERSUS" << std::endl;
}

void Bomberman::MenuComponent::Update()
{
	if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_RETURN))
	{
		Bomberman::GameManager::GetInstance().UnloadMenu();
		Bomberman::GameManager::GetInstance().LoadGame();
	}

	if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_1))
	{
		Bomberman::GameManager::GetInstance().UnloadMenu();
		Bomberman::GameManager::GetInstance().LoadSolo();
	}

	if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_2))
	{
		Bomberman::GameManager::GetInstance().UnloadMenu();
		Bomberman::GameManager::GetInstance().LoadCoop();
	}

	if (BearBones::InputManager::GetInstance().GetKeyboard()->IsPressed(SDL_SCANCODE_3))
	{
		Bomberman::GameManager::GetInstance().UnloadMenu();
		Bomberman::GameManager::GetInstance().LoadVersus();
	}

}

void Bomberman::MenuComponent::Render() const
{
}
