#include "TransformComponent.h"
#include "Entity.h"

BearBones::TransformComponent::TransformComponent(Entity* pOwner)
	: Component( pOwner )
{
}

BearBones::TransformComponent::TransformComponent(Entity* pOwner, glm::vec2 position, float rotation, glm::vec2 scale)
	: Component{ pOwner }
	, m_worldPosition{ position }
	, m_worldRotation{ rotation }
	, m_worldScale{ scale }
{
}

void BearBones::TransformComponent::Update()
{
	UpdateWorldTransform();
}

void BearBones::TransformComponent::Render() const
{
}

void BearBones::TransformComponent::RenderImGui()
{
}

void BearBones::TransformComponent::SetWorldPosition(const glm::vec2& position)
{
	if (m_pOwner->GetParent())
	{
		m_localPosition = position - m_pOwner->GetParent()->GetTransform()->GetWorldPosition();
	}
	else
	{
		m_localPosition = position;
	}
	
	m_worldPosition = position;
	m_positionDirty = false;
}

void BearBones::TransformComponent::SetWorldPosition(float x, float y)
{
	SetWorldPosition(glm::vec2(x, y));
}

void BearBones::TransformComponent::SetLocalPosition(const glm::vec2& position)
{
	m_localPosition = position;
	SetPositionDirty();
}

void BearBones::TransformComponent::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec2(x, y));
}

const glm::vec2& BearBones::TransformComponent::GetWorldPosition()
{
	if (m_positionDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

const glm::vec2& BearBones::TransformComponent::GetLocalPosition() const
{
	return m_localPosition;
}

void BearBones::TransformComponent::SetPositionDirty()
{
	m_positionDirty = true;
}

void BearBones::TransformComponent::SetWorldRotation(float rotation)
{
	if (m_pOwner->GetParent())
	{
		m_localRotation = rotation - m_pOwner->GetParent()->GetTransform()->GetWorldRotation();
	}
	else
	{
		m_localRotation = rotation;
	}
	m_rotationDirty = false;
}

void BearBones::TransformComponent::SetLocalRotation(float rotation)
{
	m_localRotation = rotation;
	SetRotationDirty();
}

float BearBones::TransformComponent::GetWorldRotation()
{
	if (m_rotationDirty)
	{
		UpdateWorldRotation();
	}
	return m_worldRotation;
}

float BearBones::TransformComponent::GetLocalRotation() const
{
	return m_localRotation;
}

void BearBones::TransformComponent::SetWorldScale(const glm::vec2& scale)
{
	if (m_pOwner->GetParent())
	{
		m_localScale = scale / m_pOwner->GetParent()->GetTransform()->GetWorldScale();
	}
	else
	{
		m_localScale = scale;
	}
	m_scaleDirty = false;
}

void BearBones::TransformComponent::SetWorldScale(float x, float y)
{
	SetWorldScale(glm::vec2(x, y));
}

void BearBones::TransformComponent::SetLocalScale(const glm::vec2& scale)
{
	m_localScale = scale;
	SetScaleDirty();
}

void BearBones::TransformComponent::SetLocalScale(float x, float y)
{
	SetLocalScale(glm::vec2(x, y));
}

const glm::vec2& BearBones::TransformComponent::GetWorldScale()
{
	if (m_scaleDirty)
	{
		UpdateWorldScale();
	}
	return m_worldScale;
}

const glm::vec2& BearBones::TransformComponent::GetLocalScale() const
{
	return m_localScale;
}

void BearBones::TransformComponent::SetRotationDirty()
{
	m_rotationDirty = true;
}

void BearBones::TransformComponent::SetScaleDirty()
{
	m_scaleDirty = true;
}

void BearBones::TransformComponent::SetDirty()
{
	SetPositionDirty();
	SetRotationDirty();
	SetScaleDirty();
}


void BearBones::TransformComponent::UpdateWorldPosition()
{
	const auto pParent = m_pOwner->GetParent();
	if (pParent)
	{
		m_worldPosition = pParent->GetTransform()->GetWorldPosition() + m_localPosition;
	}
	else
	{
		m_worldPosition = m_localPosition;
	}


	//set all children dirty so they update their world position
	for (auto pChild : m_pOwner->GetChildren())
	{
		pChild->GetTransform()->SetPositionDirty();
	}

	m_positionDirty = false;
}

void BearBones::TransformComponent::UpdateWorldRotation()
{
	const auto pParent = m_pOwner->GetParent();
	if (pParent)
	{
		m_worldRotation = pParent->GetTransform()->GetWorldRotation() + m_localRotation;
	}
	else
	{
		m_worldRotation = m_localRotation;
	}

	//set all children dirty so they update their world rotation
	for (auto pChild : m_pOwner->GetChildren())
	{
		pChild->GetTransform()->SetRotationDirty();
	}

	m_rotationDirty = false;
}

void BearBones::TransformComponent::UpdateWorldScale()
{
	const auto pParent = m_pOwner->GetParent();
	if (pParent)
	{
		m_worldScale = pParent->GetTransform()->GetWorldScale() * m_localScale;
	}
	else
	{
		m_worldScale = m_localScale;
	}

	//set all children dirty so they update their world scale
	for (auto pChild : m_pOwner->GetChildren())
	{
		pChild->GetTransform()->SetScaleDirty();
	}

	m_scaleDirty = false;
}

void BearBones::TransformComponent::UpdateWorldTransform()
{
	if (m_positionDirty)
	{
		UpdateWorldPosition();
	}
	if (m_rotationDirty)
	{
		UpdateWorldRotation();
	}
	if (m_scaleDirty)
	{
		UpdateWorldScale();
	}
}


