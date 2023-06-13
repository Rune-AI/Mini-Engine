#include "StartGameCommand.h"

#include <SceneManager.h>
#include <Scene.h>

void StartGameCommand::Execute()
{
	//get all scenes
	SceneManager::GetInstance().GetScene("MainMenu")->SetIsActive(false);
	SceneManager::GetInstance().GetScene("Stage_0")->SetIsActive(true);
	SceneManager::GetInstance().GetScene("Game")->SetIsActive(true);
}
