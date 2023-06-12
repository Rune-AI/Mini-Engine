#pragma once
#include <vector>
#include <memory>
#include <string>

//#include "Component.h"
//#include "TransformComponent.h"

class Component;
class TransformComponent;

// Component only guard
template<typename T>
concept ComponentType = std::is_base_of<Component, T>::value;

class Entity final
{
	
public:
	Entity();
	virtual ~Entity();
	Entity(const Entity& other) = delete;
	Entity(Entity&& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity& operator=(Entity&& other) = delete;


	virtual void Update();
	virtual void Render() const;
	virtual void RenderImGui();

	template<ComponentType T>
	T* GetComponent() const;

	template<ComponentType T>
	void RemoveComponent();

	template<ComponentType T>
	void AddComponent();

	template<ComponentType T, typename...Args>
	void AddComponent(Args&&... args);

	template<ComponentType T>
	bool HasComponent() const;

	void AttachChild(Entity* pChild, bool keepWorldTransform);
	void DetachChild(Entity* pChild);
	void SetParent(Entity* parent, bool keepWorldTransform);
	
	TransformComponent* GetTransform() const;
	Entity* GetParent() const;
	const std::vector<Entity*>& GetChildren() const;


	void SetActive(bool value);
	bool IsActive() const;
	void SetCanBeDestroyed(bool value);
	bool CanBeDestroyed() const;
	void MarkForDeletion();
	bool IsMarkedForDeletion() const;

	void AddTag(const std::string& tag);
	void RemoveTag(const std::string& tag);
	bool HasTag(const std::string& tag) const;

private:
	void AddChild(Entity* pChild);
	void RemoveChild(Entity* pChild);

	std::vector<std::unique_ptr<Component>> m_pComponents;
	TransformComponent* m_TransformComponent{};

	Entity* m_pParent;
	std::vector<Entity*> m_pChildren;

	std::vector<std::string> m_Tags;

	bool m_ParentsChanged{};
	bool m_IsActive{ true };
	bool m_MarkedForDeletion{ false};
	bool m_CanBeDestroyed{ true };
};


template <ComponentType T>
T* Entity::GetComponent() const
{
	for (const auto& component : m_pComponents)
	{
		T* pT = dynamic_cast<T*>(component.get());
		if (pT)
		{
			return pT;
		}
	}
	return nullptr;
}

template <ComponentType T>
void Entity::RemoveComponent()
{

	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		T* pT = dynamic_cast<T*>((*it).get());
		if (pT)
		{
			auto component = m_pComponents.at(it);
			if (component->GetCanBeRemoved())
			{
				component->MarkForDeletion();
				m_pComponents.erase(it);
			}
			return;
		}
	}
}

template <ComponentType T, typename...Args>
void Entity::AddComponent(Args&&...args)
{
	static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");
	auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
	m_pComponents.emplace_back(std::move(component));
}

template <ComponentType T>
void Entity::AddComponent()
{
	static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");
	auto component = std::make_unique<T>(this);
	m_pComponents.emplace_back(std::move(component));
}

template <ComponentType T>
bool Entity::HasComponent() const
{
	for (const auto& pComponent : m_pComponents)
	{
		if (dynamic_cast<T*>(pComponent.get()))
		{
			return true;
		}
	}
	return false;
}