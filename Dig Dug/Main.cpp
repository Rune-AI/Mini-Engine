#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include "SceneManager.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "LogService.h"
#include "PhysicsService.h"

#include <iostream>

// used in scene
#include <Scene.h>
#include <Entity.h>
#include <TextureComponent.h>
#include <TransformComponent.h>

#include "LevelComponent.h"
#include "LerpTranslateComponent.h"
#include "Player.h"
#include "PumpCommand.h"
#include "PookaComponent.h"
#include "FygarComponent.h"
#include "StageLoader.h"


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
	DigDug::StageLoader loader {};
	DigDug::Stage stage {};
	loader.LoadStage("Data/Resources/Levels/Stage_0.json", stage);

	auto& scene = SceneManager::GetInstance().CreateScene(stage.name);

	const float scaleX = windowWidth / (float(stage.cols + 4) * 16);
	const float scaleY = windowHeight / (float(stage.rows) * 16);

	const float scaledWidth = scaleX * 16;
	const float scaledHeight = scaleY * 16;

	auto sceneRoot = std::make_unique<Entity>();
	sceneRoot->GetTransform()->SetLocalScale(scaleX, scaleY);


	auto level = std::make_unique<Entity>();
	sceneRoot->AttachChild(level.get(), true);
	level->AddComponent<DigDug::LevelComponent>(stage);
	scene.Add(std::move(level));


	for (auto pos : stage.rocks)
	{
		auto rock = std::make_unique<Entity>();
		sceneRoot->AttachChild(rock.get(), false);
		float posX = (pos.col) * scaledWidth;
		float posY = (pos.row) * scaledHeight;
		rock->GetTransform()->SetLocalPosition(posX, posY);
		rock->AddComponent<TextureComponent>("Resources/Sprites/Enemies/Rock/0.png");
		scene.Add(std::move(rock));
	}
	
	for (auto pos : stage.pookas)
	{
		auto pooka = std::make_unique<Entity>();
		sceneRoot->AttachChild(pooka.get(), false);
		float posX = (pos.col) * scaledWidth;
		float posY = (pos.row) * scaledHeight;
		pooka->GetTransform()->SetLocalPosition(posX, posY);
		pooka->AddComponent<DigDug::PookaComponent>();
		scene.Add(std::move(pooka));
	}

	for (auto pos : stage.fygars)
	{
		auto fygars = std::make_unique<Entity>();
		sceneRoot->AttachChild(fygars.get(), false);
		float posX = (pos.col) * scaledWidth;
		float posY = (pos.row) * scaledHeight;
		fygars->GetTransform()->SetLocalPosition(posX, posY);
		fygars->AddComponent<DigDug::FygarComponent>();
		scene.Add(std::move(fygars));
	}


	auto player = std::make_unique<Entity>();
	sceneRoot->AttachChild(player.get(), true);
	//playerRoot->GetTransform()->SetLocalPosition(50.f, 50.f);
	player->AddComponent<DigDug::Player>();


	InputManager::GetInstance().CreateController(0);

	InputManager::GetInstance().CreateDesktopCommand<PumpCommand>(SDL_SCANCODE_SPACE, InputState::Press, player.get());
	InputManager::GetInstance().CreateConsoleCommand<PumpCommand>(XINPUT_GAMEPAD_A, InputState::Press, player.get());

	
	scene.Add(std::move(sceneRoot));
	
	scene.Add(std::move(player));
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
	ServiceLocator::RegisterSoundService(new SDLSoundSystem(4));
	ServiceLocator::RegisterPhysicsService(new PhysicsService());

	dae::Minigin engine("./Data/", windowWidth, windowHeight);
	engine.Run(load);

	ServiceLocator::DestroyServices();

	return 0;
}





