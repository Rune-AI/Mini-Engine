#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Singleton.h"
#include "Scene.h"


namespace Bomberman
{
	class GameManager final : public BearBones::Singleton<GameManager>
	{
	public:
		void ResetGame();
		void LoadOptions();
		void LoadGame();
		void UnloadGame();
		void UnloadMenu();


		void LoadSolo();
		void LoadCoop();
		void LoadVersus();

	private:
		friend class Singleton<GameManager>;
		GameManager() = default;

		BearBones::Scene* createMenuScene();
		BearBones::Scene* createGameScene();

		BearBones::Scene* createBaseGameScene();
		void RemovePreviousGame();
	};
}
#endif

