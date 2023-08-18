#include <imgui.h>
#include <imgui_plot.h>
#include "Scene.h"
#include "Entity.h"
#include "CameraComponent.h"
#include <algorithm>

unsigned int BearBones::Scene::m_idCounter = 0;

BearBones::Scene::Scene(const std::string& name) : m_name(name) {}

BearBones::Scene::~Scene() = default;

BearBones::Entity* BearBones::Scene::GetCamera() const
{
	for (const auto& object : m_objects)
	{
		if (object->HasComponent<CameraComponent>())
		{
			return object.get();
		}
	}
	return nullptr;
}

void BearBones::Scene::Add(std::unique_ptr<Entity> object)
{
	m_objects.emplace_back(std::move(object));
}

void BearBones::Scene::Remove(std::unique_ptr<Entity> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void BearBones::Scene::RemoveAll()
{
	m_objects.clear();
}

void BearBones::Scene::Update()
{
	if (!IsActive) return;

	sort(m_objects.begin(), m_objects.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b)
		{
			return a->GetZOrder() < b->GetZOrder();
		});

	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void BearBones::Scene::Render() const
{
	if (!IsActive) return;

	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void BearBones::Scene::RenderImGui()
{
	if (!IsActive) return;

	for (const auto& object : m_objects)
	{
		object->RenderImGui();
	}
}

