#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"
#include <glm/ext/vector_float2.hpp>
#include <string>


BearBones::Entity::Entity()
	: m_pParent{}
{
	AddComponent<TransformComponent>();
	m_TransformComponent = GetComponent<TransformComponent>();
}

BearBones::Entity::~Entity() = default;


void BearBones::Entity::Update()
{
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
	// todo : add erase flag, indexes to erase and erase them in update to avoid unexpected behaviors
}

void BearBones::Entity::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void BearBones::Entity::RenderImGui()
{
	for (const auto& component : m_pComponents)
	{
		component->RenderImGui();
	}
}

void BearBones::Entity::AddChild(Entity* child)
{
	m_pChildren.emplace_back(child);
}

void BearBones::Entity::RemoveChild(Entity* child)
{
	m_pChildren.erase(
		std::remove_if(m_pChildren.begin(), m_pChildren.end(), [child](auto fchild) { return fchild == child; })
	);
}

void BearBones::Entity::AttachChild(Entity* pChild, bool keepWorldTransform)
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

void BearBones::Entity::DetachChild(Entity* child)
{
	RemoveChild(child);
}

void BearBones::Entity::SetParent(Entity* parent, bool keepWorldTransform)
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

BearBones::TransformComponent* BearBones::Entity::GetTransform() const
{
	if (!m_TransformComponent)
	{
		///HUH
		assert(false);
	}
	
	return m_TransformComponent;
}

BearBones::Entity* BearBones::Entity::GetParent() const
{
	return m_pParent;
}

const std::vector<BearBones::Entity*>& BearBones::Entity::GetChildren() const
{
	return m_pChildren;
}

void BearBones::Entity::SetActive(bool value)
{
	m_IsActive = value;
}

bool BearBones::Entity::IsActive() const
{
	return m_IsActive;
}

void BearBones::Entity::SetCanBeDestroyed(bool value)
{
	m_CanBeDestroyed = value;
}

bool BearBones::Entity::CanBeDestroyed() const
{
	return m_CanBeDestroyed;
}

void BearBones::Entity::MarkForDeletion()
{
	m_MarkedForDeletion = true;
}

bool BearBones::Entity::IsMarkedForDeletion() const
{
	return m_MarkedForDeletion;
}

void BearBones::Entity::AddTag(const std::string& tag)
{
	m_Tags.emplace_back(tag);
}

void BearBones::Entity::RemoveTag(const std::string& tag)
{
	m_Tags.erase(
		std::remove_if(m_Tags.begin(), m_Tags.end(), [tag](auto ftag) { return ftag == tag; })
	);
}

bool BearBones::Entity::HasTag(const std::string& tag) const
{
	return std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end();
}
