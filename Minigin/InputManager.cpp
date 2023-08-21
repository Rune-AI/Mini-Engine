#include "InputManager.h"
#include "imgui_impl_sdl2.h"
#include <SDL.h>
#include <Xinput.h>

bool BearBones::InputManager::ProcessInput()
{
	SDL_Event e;
	UpdateConsoleInput();

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		UpdateComputerInput(e);

		ImGui_ImplSDL2_ProcessEvent(&e);

		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
			return false;
	}

	return true;
}

BearBones::XboxController* BearBones::InputManager::GetController() const
{
	return m_XboxController.get();
}

BearBones::Keyboard* BearBones::InputManager::GetKeyboard() const
{
	return m_Keyboard.get();
}

void BearBones::InputManager::CreateController(int controllerIndex)
{
	m_XboxController = std::make_unique<XboxController>(controllerIndex);
}

void BearBones::InputManager::UpdateComputerInput(SDL_Event /*event*/)
{
	m_Keyboard->Update();
}

void BearBones::InputManager::UpdateConsoleInput()
{
	if (m_XboxController)
	{
		m_XboxController->Update();
	}
}

