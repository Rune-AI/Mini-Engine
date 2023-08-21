#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"


BearBones::CameraComponent::CameraComponent(Entity* object)
	: Component{ object }
{
}

void BearBones::CameraComponent::Update()
{
	if (m_pTarget)
	{
		auto trans = m_pOwner->GetTransform();
		auto targetTrans = m_pTarget->GetTransform();
		auto Pos = targetTrans->GetWorldPosition();
		auto targetPos = targetTrans->GetWorldPosition();
		targetPos.x += m_OffsetX;
		targetPos.x = std::max(targetPos.x, m_MinX);
		targetPos.x = std::min(targetPos.x, m_MaxX);
		targetPos.y = std::max(targetPos.y, m_MinY);
		targetPos.y = std::min(targetPos.y, m_MaxY);

		//lerp

		targetPos.x = Pos.x + ((targetPos.x - Pos.x) * m_Lerp);

		trans->SetWorldPosition(targetPos);
	}
}

void BearBones::CameraComponent::Render() const
{
}

void BearBones::CameraComponent::RenderImGui()
{
}

void BearBones::CameraComponent::SetTarget(Entity* target)
{
	m_pTarget = target;
}
