#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "Entity.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "DieCommand.h"
#include "HealthHUD.h"
#include "ScoreHUD.h"
#include "ScoreCommand.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4389)
#include "CSteamAchievements.h"
#pragma warning(pop)

#include "AchievementGlobals.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include <steam_api.h>
#include "FPSCounterComponent.h"
#pragma warning(pop)

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("unique pointer test");

	auto go = std::make_unique<Entity>();
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(std::move(go));

	/*go = std::make_unique<Entity>();
	go->AddComponent<TextureComponent>(std::string("logo.tga"));
	go->GetTransform()->SetWorldPosition(216, 180);
	scene.Add(std::move(go));*/

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	//FPS
	go = std::make_unique<Entity>();
	go->AddComponent<FPSCounterComponent>(font);
	go->GetTransform()->SetLocalPosition(80, 70);
	scene.Add(std::move(go));

	//Tutorial
	go = std::make_unique<Entity>();
	go->AddComponent<TextComponent>("Player 1 controller: Die | A, Score | B", font);
	go->GetTransform()->SetLocalPosition(80, 20);
	scene.Add(std::move(go));

	go = std::make_unique<Entity>();
	go->AddComponent<TextComponent>("Player 2 keyboard: Die | F, Score | G", font);
	go->GetTransform()->SetLocalPosition(80, 50);
	scene.Add(std::move(go));
	


	//Setup Players
	auto player0 = std::make_unique<Entity>();
	player0->AddComponent<HealthComponent>();
	player0->AddComponent<ScoreComponent>();
	auto player1 = std::make_unique<Entity>();
	player1->AddComponent<HealthComponent>();
	player1->AddComponent<ScoreComponent>();
	
	//setup HUDs
	auto player0Health = std::make_unique<Entity>();
	player0Health->GetTransform()->SetLocalPosition(0, 240);
	player0Health->AddComponent<HealthHUD>(player0->GetComponent<HealthComponent>()->GetHealth());
	
	auto player0Score = std::make_unique<Entity>();
	player0Score->GetTransform()->SetLocalPosition(0, 260);
	player0Score->AddComponent<ScoreHUD>(player0->GetComponent<ScoreComponent>()->GetScore());
	
	auto player1Health = std::make_unique<Entity>();
	player1Health->GetTransform()->SetLocalPosition(0, 300);
	player1Health->AddComponent<HealthHUD>(player1->GetComponent<HealthComponent>()->GetHealth());

	auto player1Score = std::make_unique<Entity>();
	player1Score->GetTransform()->SetLocalPosition(0, 320);
	player1Score->AddComponent<ScoreHUD>(player1->GetComponent<ScoreComponent>()->GetScore());
	
	//Setup observers
	player0->GetComponent<HealthComponent>()->RegisterObserver(player0Health->GetComponent<HealthHUD>()->GetObserver());
	player1->GetComponent<HealthComponent>()->RegisterObserver(player1Health->GetComponent<HealthHUD>()->GetObserver());

	player0->GetComponent<ScoreComponent>()->RegisterObserver(player0Score->GetComponent<ScoreHUD>()->GetObserver());
	player1->GetComponent<ScoreComponent>()->RegisterObserver(player1Score->GetComponent<ScoreHUD>()->GetObserver());
	
	

	// Create controller
	InputManager::GetInstance().CreateController(0);

	// Console player
	InputManager::GetInstance().CreateConsoleCommand<DieCommand>(XINPUT_GAMEPAD_A, InputState::Press, player0.get());
	InputManager::GetInstance().CreateConsoleCommand<ScoreCommand>(XINPUT_GAMEPAD_B, InputState::Press, player0.get());

	// Desktop player
	InputManager::GetInstance().CreateDesktopCommand<DieCommand>(SDL_SCANCODE_F, InputState::Press, player1.get());
	InputManager::GetInstance().CreateDesktopCommand<ScoreCommand>(SDL_SCANCODE_G, InputState::Press, player1.get());


	// add all entities to scene
	scene.Add(std::move(player0));
	scene.Add(std::move(player1));
	scene.Add(std::move(player0Health));
	scene.Add(std::move(player1Health));
	scene.Add(std::move(player0Score));
	scene.Add(std::move(player1Score));

}

int main(int, char*[]) {

	if (SteamAPI_Init())
	{
		CSteamAchievements::GetInstance().Setup(g_Achievements, 4);
	}
	

	dae::Minigin engine("../Data/");
	engine.Run(load);

	if (!SteamAPI_Init())
	{
		SteamAPI_Shutdown();
	}
	
    return 0;
}