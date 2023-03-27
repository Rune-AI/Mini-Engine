#include <imgui.h>
#include <imgui_plot.h>
#include "Scene.h"
#include "Entity.h"

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<Entity> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<Entity> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::RenderImGui()
{
	for (const auto& object : m_objects)
	{
		object->RenderImGui();
	}
}

