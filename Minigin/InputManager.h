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
	template<class T>
	concept CommandType = std::is_base_of<T, Command>::value;

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

		template<typename T>
		void CreateConsoleCommand(int key, InputState state, class Entity* entity);

		template<typename T>
		void CreateDesktopCommand(int key, InputState state, class Entity* entity);

		void CreateController(int controllerIndex);

	private:

		void UpdateComputerInput(SDL_Event event);
		void UpdateConsoleInput();

		using CommandsMap = std::map<int, std::pair<InputState, std::unique_ptr<Command>>>;

		CommandsMap m_ConsoleCommands{};
		CommandsMap m_DesktopCommands{};

		std::unique_ptr<XboxController> m_XboxController{};
		std::unique_ptr<Keyboard> m_Keyboard{std::make_unique<Keyboard>()};
	};

	template<typename CommandType>
	void InputManager::CreateConsoleCommand(int key, InputState state, Entity* entity)
	{
		std::unique_ptr<CommandType> command = std::make_unique<CommandType>(entity);
		m_ConsoleCommands.insert(std::pair{ key, std::pair{state, std::move(command)} });
	}

	template<typename CommandType>
	void InputManager::CreateDesktopCommand(int key, InputState state, Entity* entity)
	{
		std::unique_ptr<CommandType> command = std::make_unique<CommandType>(entity);
		m_DesktopCommands.insert(std::pair{ key, std::pair{state, std::move(command)} });
	}
}

#endif //INPUT_MANAGER_H