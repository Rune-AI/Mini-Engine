#include <memory>
#include "SceneManager.h"
#include "Scene.h"

void BearBones::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void BearBones::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void BearBones::SceneManager::RenderImGui()
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderImGui();
	}
}

BearBones::Scene* BearBones::SceneManager::GetScene(std::string name) const
{
	for(const auto& scene : m_scenes)
	{
		if (scene->GetName() == name)
		{
			return scene.get();
		}
	}
	return nullptr;
}

BearBones::Scene* BearBones::SceneManager::GetActiveScene() const
{
	for (const auto& scene : m_scenes)
	{
		if (scene->GetIsActive())
		{
			return scene.get();
		}
	}
	return nullptr;
}

BearBones::Scene& BearBones::SceneManager::CreateScene(const std::string& name)
{
	//const auto& scene = std::unique_ptr<Scene>(std::make_unique<Scene>(name));
	m_scenes.push_back(std::make_unique<Scene>(name));
	return *m_scenes.back();
}
