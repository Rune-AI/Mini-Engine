#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "XboxController.h"
#include "Keyboard.h"
#include "Singleton.h"
#include <Xinput.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include "Command.h"
#include <map>

namespace BearBones
{
	enum class InputState
	{
		Hold,
		Press,
		Release
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		XboxController* GetController() const;
		Keyboard* GetKeyboard() const;

		void CreateController(int controllerIndex);

	private:

		void UpdateComputerInput(SDL_Event event);
		void UpdateConsoleInput();

		std::unique_ptr<XboxController> m_XboxController{};
		std::unique_ptr<Keyboard> m_Keyboard{std::make_unique<Keyboard>()};
	};
}

#endif //INPUT_MANAGER_H