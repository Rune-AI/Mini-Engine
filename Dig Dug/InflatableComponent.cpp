#include "InflatableComponent.h"
#include <RigidBody2DComponent.h>
#include <Entity.h>

DigDug::InflatableComponent::InflatableComponent(Entity* object)
	: Component{ object }
{

	
	if (!GetOwner()->HasComponent<RigidBody2DComponent>())
	{
        GetOwner()->AddComponent<RigidBody2DComponent>(50.f, 50.f);
	}
	auto rb = GetOwner()->GetComponent<RigidBody2DComponent>();

    rb->SetOnCollisionEnterCallback([this](RigidBody2DComponent* other)
        {
            if (other->GetOwner()->HasTag("Pump"))
            {
                NotifyObservers(other->GetOwner());
            }
        });

    rb->SetOnCollisionExitCallback([this](RigidBody2DComponent*)
        {
        });

    rb->SetOnCollisionCallback([this](RigidBody2DComponent*)
        {
        });

}
