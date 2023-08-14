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

#include <iostream>

// used in scene
#include <Scene.h>
#include <Entity.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>

#include "LevelComponent.h"
#include "LerpTranslateComponent.h"
#include "Player.h"
#include "PumpCommand.h"
#include "PookaComponent.h"
#include "FygarComponent.h"
#include "StageLoader.h"
#include "StartGameCommand.h"

#include <SDLSoundSystem.h>


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
	std::cout << "Pump: [SPACE]\n";
	std::cout << "player 1 CONTROLLER:\n";
	std::cout << "Move: [LEFT STICK]\n";
	std::cout << "Pump: [A]\n";
}


using namespace BearBones;

Scene* createMenuScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("MainMenu");

	auto background = std::make_unique<Entity>();
	background->AddComponent<TextureComponent>("background.tga");

	auto logo = std::make_unique<Entity>();
	logo->AddComponent<BearBones::TextureComponent>("Resources/Sprites/Logo.png");
	int logoWidth = logo->GetComponent<TextureComponent>()->GetTextureSize().x;
	logo->GetTransform()->SetLocalPosition(windowWidth/2.f - logoWidth/2.f, 50.f);


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	auto playButton = std::make_unique<Entity>();
	playButton->AddComponent<TextComponent>("SOLO", font);
	playButton->GetTransform()->SetLocalPosition(windowWidth / 2.f - logoWidth / 2.f - 50.f, 200.f);

	InputManager::GetInstance().CreateDesktopCommand<StartGameCommand>(SDL_SCANCODE_RETURN, InputState::Press, playButton.get());
	InputManager::GetInstance().CreateConsoleCommand<StartGameCommand>(XINPUT_GAMEPAD_START, InputState::Press, playButton.get());

	scene.Add(std::move(background));
	scene.Add(std::move(logo));
	scene.Add(std::move(playButton));

	return &scene;
}

void load()
{
	printControls();
	auto menuScene = createMenuScene();
	menuScene->SetIsActive(true);
}


int main(int, char* [])
{
	BearBones::ServiceLocator::RegisterSoundService(new BearBones::SDLSoundSystem(4));

	Minigin engine("./Data/", windowWidth, windowHeight);
	engine.Run(load);

	BearBones::ServiceLocator::DestroyServices();

	return 0;
}





