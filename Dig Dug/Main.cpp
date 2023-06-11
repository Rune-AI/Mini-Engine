#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include "SceneManager.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "PhysicsService.h"
#include "SDLSoundSystem.h"
#include "LogService.h"

#include <iostream>

// used in scene
#include <Scene.h>
#include <Entity.h>
#include <TextureComponent.h>
#include <TransformComponent.h>

#include "LerpTranslateComponent.h"
#include "Player.h"


constexpr auto windowWidth = 640;
constexpr auto windowHeight = 480;

void printControls()
{
	std::cout << "----------------- Controls -----------------\n";
	std::cout << "----------------- Menu -----------------\n";
	std::cout << "Up/Down: [Arrow keys]\n";
	std::cout << "Select: [Enter]\n";
	std::cout << "----------------- Game -----------------\n";
	std::cout << "player 0 KEYBOARD:\n";
	std::cout << "Move: [WASD]\n";
	std::cout << "Pump: [Space]\n";
	std::cout << "player 1 CONTROLLER:\n";
	std::cout << "Move: [DPAD]\n";
	std::cout << "Pump: [A]\n";
}


Scene* createMenuScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("MainMenu");

	auto background = std::make_unique<Entity>();
	background->AddComponent<TextureComponent>("background.tga");

	auto anchor = std::make_unique<Entity>();
	anchor->GetTransform()->SetLocalPosition(0.f, windowHeight); //bottom of the page so it can move up
	anchor->AddComponent<DigDug::LerpTranslateComponent>(0.f, 0.f, 2.f);

	auto logo = std::make_unique<Entity>();
	logo->AddComponent<TextureComponent>("Resources/Sprites/Logo.png");
	int logoWidth = logo->GetComponent<TextureComponent>()->GetTextureSize().x;
	logo->GetTransform()->SetLocalPosition(windowWidth/2.f - logoWidth/2.f, 50.f);

	anchor->AttachChild(logo.get(), false);

	scene.Add(std::move(background));
	scene.Add(std::move(anchor));
	scene.Add(std::move(logo));

	return &scene;
}


Scene* createGameScene()
{
	// has all the lives, UI, etc
	auto& scene = SceneManager::GetInstance().CreateScene("Level");

	auto background = std::make_unique<Entity>();
	background->AddComponent<TextureComponent>("background.tga");

	scene.Add(std::move(background));

	return &scene;
}


Scene* createLevelScene()
{
	// has all the enemies, players, level, etc
	auto& scene = SceneManager::GetInstance().CreateScene("Game");

	auto playerRoot = std::make_unique<Entity>();
	playerRoot->AddComponent<DigDug::Player>();
	playerRoot->AddComponent<TextureComponent>("Resources/Sprites/Logo.png");

	scene.Add(std::move(playerRoot));

	return &scene;
}

void load()
{
	printControls();
	auto menuScene = createMenuScene();
	auto gameScene = createGameScene();
	auto levelScene = createLevelScene();

	menuScene->SetIsActive(false);
	gameScene->SetIsActive(true);
	levelScene->SetIsActive(true);


	//auto& scene = SceneManager::GetInstance().CreateScene("GameIntro");
	//InputManager::GetInstance().CreateController(0);

}


int main(int, char* [])
{
	/*#ifdef DEBUG
		ServiceLocator::RegisterSoundService(new LogService(new SDLSoundSystem(4)));
	#else
	#endif*/

	ServiceLocator::RegisterSoundService(new SDLSoundSystem(4));
	ServiceLocator::RegisterPhysicsService(new PhysicsService());

	dae::Minigin engine("./Data/");
	engine.Run(load);

	ServiceLocator::DestroyServices();

	return 0;
}





