#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

constexpr auto windowWidth = 640;
constexpr auto windowHeight = 640;

using namespace BearBones;


#include <Renderer.h>
#include <Scene.h>
#include <TextureComponent.h>
#include <CameraComponent.h>
#include <TransformComponent.h>

#include "LevelComponent.h"
#include "EnemyAIController.h"
#include "AnimationComponent.h"
#include "EntityFactory.h"
#include "PlayerController.h"
#include "DestructableComponent.h"
#include "DoorComponent.h"

#include "GameManager.h"
#include <ServiceLocator.h>
#include <SDLSoundSystem.h>
#include <ResourceManager.h>

Scene* createGameScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Game");

	auto camera = std::make_unique<Entity>();
	camera->AddComponent<CameraComponent>();
	//camera->GetTransform()->SetLocalPosition(100.f, 100.f);



	auto background = std::make_unique<Entity>();
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


	float cameraScale = float(windowHeight)/ backgroundSize.y;
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

void load()
{
	Bomberman::GameManager::GetInstance().LoadOptions();

	BearBones::ServiceLocator::GetSoundService()->PlaySimple("Resources/Sounds/Menu2.mp3", 50000);

	/*auto gameScene = createGameScene();
	gameScene->SetIsActive(true);*/
}


int main(int, char* [])
{
	BearBones::ServiceLocator::RegisterSoundService(new BearBones::SDLSoundSystem(4));

	Minigin engine("./BombermanData/", windowWidth, windowHeight);
	engine.Run(load);

	BearBones::ServiceLocator::DestroyServices();

	return 0;
}