#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
//#include "Scene.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
		
	virtual ~SceneManager() override = default;
	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) = delete;

	void Update();
	void Render();
	void RenderImGui();
	Scene* GetScene(std::string name) const;


private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::unique_ptr<Scene>> m_scenes;
};
