#include "StartGameCommand.h"

#include <SceneManager.h>
#include <Scene.h>

void StartGameCommand::Execute()
{
	//get all scenes
	BearBones::SceneManager::GetInstance().GetScene("MainMenu")->SetIsActive(false);
	BearBones::SceneManager::GetInstance().GetScene("Stage_0")->SetIsActive(true);
	BearBones::SceneManager::GetInstance().GetScene("Game")->SetIsActive(true);
}
