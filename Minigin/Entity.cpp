#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"
#include <glm/ext/vector_float2.hpp>


Entity::Entity()
	: m_pParent{}
{
	AddComponent<TransformComponent>();
	m_TransformComponent = GetComponent<TransformComponent>();
}

Entity::~Entity() = default;


void Entity::Update()
{
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
	// todo : add erase flag, indexes to erase and erase them in update to avoid unexpected behaviors
}

void Entity::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void Entity::RenderImGui()
{
	for (const auto& component : m_pComponents)
	{
		component->RenderImGui();
	}
}

void Entity::AddChild(Entity* child)
{
	m_pChildren.emplace_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	m_pChildren.erase(
		std::remove_if(m_pChildren.begin(), m_pChildren.end(), [child](auto fchild) { return fchild == child; })
	);
}

void Entity::AttachChild(Entity* pChild, bool keepWorldTransform)
{
	auto pChildTransform = pChild->GetTransform();

	if (keepWorldTransform)
	{
		pChildTransform->SetLocalPosition(pChildTransform->GetLocalPosition() - GetTransform()->GetWorldPosition());
		pChildTransform->SetPositionDirty();
	}
	else
	{
		pChildTransform->SetLocalPosition(pChildTransform->GetWorldPosition());
	}
	
	if (auto parentOfChild = pChild->GetParent(); parentOfChild != nullptr)
	{
		parentOfChild->DetachChild(pChild);
	}

	if (pChild->m_pParent = this; pChild->m_pParent != nullptr)
	{
		AddChild(pChild);
	}
}

void Entity::DetachChild(Entity* child)
{
	RemoveChild(child);
}

void Entity::SetParent(Entity* parent, bool keepWorldTransform)
{
	if (parent == nullptr)
		GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	else
	{
		if (keepWorldTransform)
			GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() -
				GetParent()->GetTransform()->GetWorldPosition());
		GetTransform()->SetDirty();
	}
	Entity* child{};
	if (m_pParent != nullptr)
		for (auto it = m_pParent->m_pChildren.begin(); it != m_pParent->m_pChildren.end(); ++it)
			if (*it == this)
			{
				child = std::move(*it);
				m_pParent->m_pChildren.erase(it);
				break;
			}
	m_pParent = parent;
	if (m_pParent != nullptr)
	{
		if (child == nullptr)
			child = this;
		m_pParent->m_pChildren.emplace_back(std::move(child));
	}
}

TransformComponent* Entity::GetTransform() const
{
	if (!m_TransformComponent)
	{
		///HUH
	}
	
	return m_TransformComponent;
}

Entity* Entity::GetParent() const
{
	return m_pParent;
}

const std::vector<Entity*>& Entity::GetChildren() const
{
	return m_pChildren;
}

void Entity::SetActive(bool value)
{
	m_IsActive = value;
}

bool Entity::IsActive() const
{
	return m_IsActive;
}

void Entity::SetCanBeDestroyed(bool value)
{
	m_CanBeDestroyed = value;
}

bool Entity::CanBeDestroyed() const
{
	return m_CanBeDestroyed;
}

void Entity::MarkForDeletion()
{
	m_MarkedForDeletion = true;
}

bool Entity::IsMarkedForDeletion() const
{
	return m_MarkedForDeletion;
}
