#pragma once
#include "InputManager.h"
#include "imgui_impl_sdl2.h"
#include <SDL.h>
#include <Xinput.h>

bool InputManager::ProcessInput()
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

	int keys{};
	auto state = SDL_GetKeyboardState(&keys);
	for (auto& command : m_DesktopCommands)
	{
		if (state[command.first] && command.second.first == InputState::Hold)
		{
			command.second.second->Execute();
		}
	}

	return true;
}

XboxController* InputManager::GetController() const
{
	return m_XboxController.get();
}

Keyboard* InputManager::GetKeyboard() const
{
	return m_Keyboard.get();
}

void InputManager::CreateController(int controllerIndex)
{
	m_XboxController = std::make_unique<XboxController>(controllerIndex);
}

void InputManager::UpdateComputerInput(SDL_Event event)
{
	m_Keyboard->Update();

	for (auto& command : m_DesktopCommands)
	{
		auto key = event.key.keysym.scancode;

		if (command.first != key)
			continue;

		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (command.second.first == InputState::Press && event.key.repeat == 0)
			{
				command.second.second->Execute();
			}
			break;
		case SDL_KEYUP:
			if (command.second.first == InputState::Release)
			{
				command.second.second->Execute();
			}
			break;
		}
	}
}

void InputManager::UpdateConsoleInput()
{
	if (m_XboxController)
	{
		m_XboxController->Update();

		for (auto& command : m_ConsoleCommands)
		{
			switch (command.second.first)
			{
			case InputState::Press:
				if (m_XboxController->IsDownThisFrame(command.first))
				{
					command.second.second->Execute();
				}
				break;
			case InputState::Hold:
				if (m_XboxController->IsPressed(command.first))
				{
					command.second.second->Execute();
				}
				break;
			case InputState::Release:
				if (m_XboxController->IsUpThisFrame(command.first))
				{
					command.second.second->Execute();
				}
				break;
			}

		}
	}
}

