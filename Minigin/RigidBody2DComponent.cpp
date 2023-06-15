#include "RigidBody2DComponent.h"
#include "ServiceLocator.h"
//#include "PhysicsService.h"
#include "Entity.h"

BearBones::RigidBody2DComponent::RigidBody2DComponent(Entity* object, const float width, const float height)
    : Component(object)
{
    m_Collider.width = width;
    m_Collider.height = height;

    //ServiceLocator::GetPhysicsService()->AddRigidBody(this);
    GetOwner()->SetCanBeDestroyed(false);
}