#include "RigidBody2DComponent.h"
#include "ServiceLocator.h"
#include "PhysicsService.h"
#include "Entity.h"

RigidBody2DComponent::RigidBody2DComponent(Entity* object, const BoxCollider collider)
    : Component(object)
    , m_Collider{ collider }
{
    ServiceLocator::GetPhysicsService()->AddRigidBody(this);
    GetOwner()->SetCanBeDestroyed(false);
}