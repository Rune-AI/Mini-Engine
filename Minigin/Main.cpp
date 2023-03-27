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
#include "Scene.h"
#include "Entity.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("unique pointer test");

	auto go = std::make_unique<Entity>();
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(std::move(go));

	go = std::make_unique<Entity>();
	go->AddComponent<TextureComponent>(std::string("logo.tga"));
	go->GetTransform()->SetWorldPosition(216, 180);
	scene.Add(std::move(go));

	go = std::make_unique<Entity>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->GetTransform()->SetLocalPosition(80, 20);
	scene.Add(std::move(go));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}