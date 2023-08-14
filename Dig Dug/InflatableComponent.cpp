#include "InflatableComponent.h"
#include <RigidBody2DComponent.h>
#include <Entity.h>

DigDug::InflatableComponent::InflatableComponent(BearBones::Entity* object)
	: Component{ object }
{

	
	if (!GetOwner()->HasComponent<BearBones::RigidBody2DComponent>())
	{
        GetOwner()->AddComponent<BearBones::RigidBody2DComponent>(50.f, 50.f);
	}
	auto rb = GetOwner()->GetComponent<BearBones::RigidBody2DComponent>();

    rb->SetOnCollisionEnterCallback([this](BearBones::RigidBody2DComponent* other)
        {
            if (other->GetOwner()->HasTag("Pump"))
            {
                NotifyObservers(other->GetOwner());
            }
        });

    rb->SetOnCollisionExitCallback([this](BearBones::RigidBody2DComponent*)
        {
        });

    rb->SetOnCollisionCallback([this](BearBones::RigidBody2DComponent*)
        {
        });

}
