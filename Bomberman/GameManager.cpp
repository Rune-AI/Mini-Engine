#include "GameManager.h"
#include <SceneManager.h>
#include <Scene.h>
#include <iostream>
#include "LevelComponent.h"
#include "EnemyAIController.h"
#include "AnimationComponent.h"
#include "EntityFactory.h"
#include "PlayerController.h"
#include "DestructableComponent.h"
#include "DoorComponent.h"
#include <CameraComponent.h>
#include <TransformComponent.h>
#include "MenuComponent.h"
#include "DebugComponent.h"
using namespace BearBones;

constexpr auto windowWidth = 640;
constexpr auto windowHeight = 640;


void Bomberman::GameManager::ResetGame()
{
	std::cout << "Resetting game" << std::endl;
	UnloadGame();
	/*Load();
	auto gameScene = createGameScene();
	gameScene->SetIsActive(true);*/
}

void Bomberman::GameManager::LoadOptions()
{
	auto scene = BearBones::SceneManager::GetInstance().GetScene("Menu");
	if (scene)
	{
		scene->SetIsActive(false);
		scene->RemoveAll();
	}
	BearBones::SceneManager::GetInstance().RemoveScene("Menu");

	auto menuScene = createMenuScene();
	menuScene->SetIsActive(true);
}

void Bomberman::GameManager::LoadGame()
{
	auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");
	if (scene)
	{
		scene->SetIsActive(false);
		scene->RemoveAll();
	}
	BearBones::SceneManager::GetInstance().RemoveScene("Game");
	
	auto gameScene = createGameScene();
	gameScene->SetIsActive(true);
}

void Bomberman::GameManager::UnloadGame()
{
	auto gameScene = BearBones::SceneManager::GetInstance().GetScene("Game");
	if (gameScene)
	{
		gameScene->SetIsActive(false);
	}
	BearBones::SceneManager::GetInstance().GetScene("Menu")->SetIsActive(true);
}

void Bomberman::GameManager::UnloadMenu()
{
	BearBones::SceneManager::GetInstance().GetScene("Menu")->SetIsActive(false);
}

void Bomberman::GameManager::LoadSolo()
{
	RemovePreviousGame();
	auto scene = createBaseGameScene();

	auto camera = std::make_unique<BearBones::Entity>();
	camera->AddComponent<CameraComponent>();

	auto background = std::make_unique<BearBones::Entity>();
	background->AddComponent<TextureComponent>("Resources/Backgrounds/Playfield.png");
	background->SetZOrder(-1);
	auto backgroundSize = background->GetComponent<TextureComponent>()->GetTextureSize();
	int backgroundTileSize = 16;
	

	auto Level = std::make_unique<Entity>();
	Level->AddComponent<Bomberman::LevelComponent>(backgroundSize.x / backgroundTileSize, backgroundSize.y / backgroundTileSize);


	Bomberman::EntityFactory entityFactory{};
	auto player = entityFactory.CreatePlayer(Level.get());
	player->GetTransform()->SetLocalPosition(16.f, 16.f);


	float cameraScale = float(windowHeight) / backgroundSize.y;
	camera->GetTransform()->SetLocalScale(cameraScale, cameraScale);

	auto levelComp = Level->GetComponent<Bomberman::LevelComponent>();
	levelComp->AddPlayer(player.get());
	levelComp->SpawnEnemies();
	levelComp->SetTriggers();

	camera->GetComponent<CameraComponent>()->SetTarget(player.get());

	scene->Add(std::move(camera));
	scene->Add(std::move(player));
	scene->Add(std::move(Level));
	scene->Add(std::move(background));
	scene->SetIsActive(true);
}

void Bomberman::GameManager::LoadCoop()
{
	RemovePreviousGame();
	auto scene = createBaseGameScene();

	auto camera = std::make_unique<BearBones::Entity>();
	camera->AddComponent<CameraComponent>();

	auto background = std::make_unique<BearBones::Entity>();
	background->AddComponent<TextureComponent>("Resources/Backgrounds/Playfield.png");
	background->SetZOrder(-1);
	auto backgroundSize = background->GetComponent<TextureComponent>()->GetTextureSize();
	int backgroundTileSize = 16;


	auto Level = std::make_unique<Entity>();
	Level->AddComponent<Bomberman::LevelComponent>(backgroundSize.x / backgroundTileSize, backgroundSize.y / backgroundTileSize);


	Bomberman::EntityFactory entityFactory{};
	auto player1 = entityFactory.CreatePlayer(Level.get());
	player1->GetTransform()->SetLocalPosition(16.f, 16.f);
	player1->GetComponent<Bomberman::PlayerController>()->SetUseWASD(true);
	player1->GetComponent<Bomberman::PlayerController>()->SetUseArrows(false);
	player1->GetComponent<Bomberman::PlayerController>()->SetUseController(false);


	auto player2 = entityFactory.CreatePlayer(Level.get());
	player2->GetTransform()->SetLocalPosition(32.f, 16.f);
	player2->GetComponent<Bomberman::PlayerController>()->SetUseWASD(false);
	player2->GetComponent<Bomberman::PlayerController>()->SetUseArrows(true);
	player2->GetComponent<Bomberman::PlayerController>()->SetUseController(true);
	


	float cameraScale = float(windowHeight) / backgroundSize.y;
	camera->GetTransform()->SetLocalScale(cameraScale, cameraScale);

	auto levelComp = Level->GetComponent<Bomberman::LevelComponent>();
	levelComp->AddPlayer(player1.get());
	levelComp->AddPlayer(player2.get());
	levelComp->SpawnEnemies();
	levelComp->SetTriggers();

	camera->GetComponent<CameraComponent>()->SetTarget(player1.get());

	scene->Add(std::move(camera));
	scene->Add(std::move(player1));
	scene->Add(std::move(player2));
	scene->Add(std::move(Level));
	scene->Add(std::move(background));
	scene->SetIsActive(true);
}

void Bomberman::GameManager::LoadVersus()
{
	RemovePreviousGame();
	auto scene = createBaseGameScene();

	auto camera = std::make_unique<BearBones::Entity>();
	camera->AddComponent<CameraComponent>();

	auto background = std::make_unique<BearBones::Entity>();
	background->AddComponent<TextureComponent>("Resources/Backgrounds/Playfield.png");
	background->SetZOrder(-1);
	auto backgroundSize = background->GetComponent<TextureComponent>()->GetTextureSize();
	int backgroundTileSize = 16;


	auto Level = std::make_unique<Entity>();
	Level->AddComponent<Bomberman::LevelComponent>(backgroundSize.x / backgroundTileSize, backgroundSize.y / backgroundTileSize);


	Bomberman::EntityFactory entityFactory{};
	auto player1 = entityFactory.CreatePlayer(Level.get());
	player1->GetTransform()->SetLocalPosition(16.f, 16.f);
	player1->GetComponent<Bomberman::PlayerController>()->SetUseWASD(true);
	player1->GetComponent<Bomberman::PlayerController>()->SetUseArrows(false);
	player1->GetComponent<Bomberman::PlayerController>()->SetUseController(false);


	auto player2 = entityFactory.CreateBalloomVisual(Level.get());
	player2->AddComponent<Bomberman::PlayerController>(Level.get(), false, true, true);
	player2->GetTransform()->SetLocalPosition(32.f, 16.f);
	player2->GetComponent<Bomberman::PlayerController>()->SetUseWASD(false);
	player2->GetComponent<Bomberman::PlayerController>()->SetUseArrows(true);
	player2->GetComponent<Bomberman::PlayerController>()->SetUseController(true);
	player2->GetComponent<Bomberman::PlayerController>()->SetSpeed(48.f);



	float cameraScale = float(windowHeight) / backgroundSize.y;
	camera->GetTransform()->SetLocalScale(cameraScale, cameraScale);

	auto levelComp = Level->GetComponent<Bomberman::LevelComponent>();
	levelComp->AddPlayer(player1.get());
	levelComp->AddPlayer(player2.get());
	levelComp->SpawnEnemies();
	levelComp->SetTriggers();

	camera->GetComponent<CameraComponent>()->SetTarget(player1.get());

	scene->Add(std::move(camera));
	scene->Add(std::move(player1));
	scene->Add(std::move(player2));
	scene->Add(std::move(Level));
	scene->Add(std::move(background));
	scene->SetIsActive(true);
}




BearBones::Scene* Bomberman::GameManager::createMenuScene()
{
	auto& scene = BearBones::SceneManager::GetInstance().CreateScene("Menu");

	auto debug = std::make_unique<BearBones::Entity>();
	debug->AddComponent<DebugComponent>();
	scene.Add(std::move(debug));

	auto camera = std::make_unique<BearBones::Entity>();
	camera->AddComponent<CameraComponent>();
	camera->GetTransform()->SetLocalScale(2.f, 2.f);

	auto background = std::make_unique<BearBones::Entity>();
	background->AddComponent<TextureComponent>("Resources/Backgrounds/Titlescreen.png");
	background->SetZOrder(-1);

	auto Menu = std::make_unique<Entity>();
	Menu->AddComponent<Bomberman::MenuComponent>();

	scene.Add(std::move(background));
	scene.Add(std::move(Menu));
	scene.Add(std::move(camera));

	return &scene;
}

BearBones::Scene* Bomberman::GameManager::createGameScene()
{
	auto& scene = BearBones::SceneManager::GetInstance().CreateScene("Game");

	auto debug = std::make_unique<BearBones::Entity>();
	debug->AddComponent<DebugComponent>();
	scene.Add(std::move(debug));


	auto camera = std::make_unique<BearBones::Entity>();
	camera->AddComponent<CameraComponent>();
	//camera->GetTransform()->SetLocalPosition(100.f, 100.f);



	auto background = std::make_unique<BearBones::Entity>();
	background->AddComponent<TextureComponent>("Resources/Backgrounds/Playfield.png");
	background->SetZOrder(-1);
	auto backgroundSize = background->GetComponent<TextureComponent>()->GetTextureSize();
	int backgroundTileSize = 16;

	auto Level = std::make_unique<Entity>();
	Level->AddComponent<Bomberman::LevelComponent>(backgroundSize.x / backgroundTileSize, backgroundSize.y / backgroundTileSize);


	Bomberman::EntityFactory entityFactory{};
	auto player = entityFactory.CreatePlayer(Level.get());
	player->AddComponent<Bomberman::PlayerController>(Level.get());
	player->GetTransform()->SetLocalPosition(16.f, 16.f);


	float cameraScale = float(windowHeight) / backgroundSize.y;
	camera->GetTransform()->SetLocalScale(cameraScale, cameraScale);

	auto levelComp = Level->GetComponent<Bomberman::LevelComponent>();
	levelComp->AddPlayer(player.get());
	levelComp->SpawnEnemies();
	levelComp->SetTriggers();


	//auto door = entityFactory.CreateDoor(Level.get());
	//door->GetComponent<Bomberman::DoorComponent>()->AddObserver(player.get());
	//door->GetTransform()->SetLocalPosition(16.f, 48.f);

	//scene.Add(std::move(door));


	camera->GetComponent<CameraComponent>()->SetTarget(player.get());

	scene.Add(std::move(camera));
	scene.Add(std::move(player));
	scene.Add(std::move(Level));
	scene.Add(std::move(background));
	return &scene;
}

BearBones::Scene* Bomberman::GameManager::createBaseGameScene()
{
	auto& scene = BearBones::SceneManager::GetInstance().CreateScene("Game");

	auto debug = std::make_unique<BearBones::Entity>();
	debug->AddComponent<DebugComponent>();
	scene.Add(std::move(debug));

	return &scene;
}

void Bomberman::GameManager::RemovePreviousGame()
{
	auto scene = BearBones::SceneManager::GetInstance().GetScene("Game");
	if (scene)
	{
		scene->SetIsActive(false);
		scene->RemoveAll();
	}
	BearBones::SceneManager::GetInstance().RemoveScene("Game");
}



