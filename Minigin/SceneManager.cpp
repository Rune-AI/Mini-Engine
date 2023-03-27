#include <memory>
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void SceneManager::RenderImGui()
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderImGui();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	//const auto& scene = std::unique_ptr<Scene>(std::make_unique<Scene>(name));
	m_scenes.push_back(std::make_unique<Scene>(name));
	return *m_scenes.back();
}
