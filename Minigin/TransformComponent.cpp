#include "TransformComponent.h"
#include "Entity.h"

TransformComponent::TransformComponent(Entity* pOwner)
	: Component( pOwner )
{
}

TransformComponent::TransformComponent(Entity* pOwner, glm::vec2 position, float rotation, glm::vec2 scale)
	: Component{ pOwner }
	, m_worldPosition{ position }
	, m_worldRotation{ rotation }
	, m_worldScale{ scale }
{
}

void TransformComponent::Update()
{
	UpdateWorldTransform();
}

void TransformComponent::Render() const
{
}

void TransformComponent::RenderImGui()
{
}

void TransformComponent::SetWorldPosition(const glm::vec2& position)
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

void TransformComponent::SetWorldPosition(float x, float y)
{
	SetWorldPosition(glm::vec2(x, y));
}

void TransformComponent::SetLocalPosition(const glm::vec2& position)
{
	m_localPosition = position;
	SetPositionDirty();
}

void TransformComponent::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec2(x, y));
}

const glm::vec2& TransformComponent::GetWorldPosition()
{
	if (m_positionDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

const glm::vec2& TransformComponent::GetLocalPosition() const
{
	return m_localPosition;
}

void TransformComponent::SetPositionDirty()
{
	m_positionDirty = true;
}

void TransformComponent::SetWorldRotation(float rotation)
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

void TransformComponent::SetLocalRotation(float rotation)
{
	m_localRotation = rotation;
	SetRotationDirty();
}

float TransformComponent::GetWorldRotation()
{
	if (m_rotationDirty)
	{
		UpdateWorldRotation();
	}
	return m_worldRotation;
}

float TransformComponent::GetLocalRotation() const
{
	return m_localRotation;
}

void TransformComponent::SetWorldScale(const glm::vec2& scale)
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

void TransformComponent::SetWorldScale(float x, float y)
{
	SetWorldScale(glm::vec2(x, y));
}

void TransformComponent::SetLocalScale(const glm::vec2& scale)
{
	m_localScale = scale;
	SetScaleDirty();
}

void TransformComponent::SetLocalScale(float x, float y)
{
	SetLocalScale(glm::vec2(x, y));
}

const glm::vec2& TransformComponent::GetWorldScale()
{
	if (m_scaleDirty)
	{
		UpdateWorldScale();
	}
	return m_worldScale;
}

const glm::vec2& TransformComponent::GetLocalScale() const
{
	return m_localScale;
}

void TransformComponent::SetRotationDirty()
{
	m_rotationDirty = true;
}

void TransformComponent::SetScaleDirty()
{
	m_scaleDirty = true;
}

void TransformComponent::SetDirty()
{
	SetPositionDirty();
	SetRotationDirty();
	SetScaleDirty();
}


void TransformComponent::UpdateWorldPosition()
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
	m_positionDirty = false;
}

void TransformComponent::UpdateWorldRotation()
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
	m_rotationDirty = false;
}

void TransformComponent::UpdateWorldScale()
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
	m_scaleDirty = false;
}

void TransformComponent::UpdateWorldTransform()
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


