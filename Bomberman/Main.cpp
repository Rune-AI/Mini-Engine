#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
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
	


	float cameraScale = float(windowHeight)/ backgroundSize.y;
	camera->GetTransform()->SetLocalScale(cameraScale, cameraScale);


	//scene.Add(std::move(camera));
	scene.Add(std::move(Level));
	scene.Add(std::move(background));
	return &scene;
}

void load()
{
	auto gameScene = createGameScene();
	gameScene->SetIsActive(true);

}


int main(int, char* [])
{
	Minigin engine("./BombermanData/", windowWidth, windowHeight);
	engine.Run(load);

	return 0;
}