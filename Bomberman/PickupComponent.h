#ifndef PICKUP_COMPONENT_H
#define PICKUP_COMPONENT_H

#include "Component.h"
#include <IObserver.h>
#include "PlayerController.h"

namespace Bomberman
{
	class PickupComponent : public BearBones::Component, public BearBones::IObserver<PlayerController*, int>
	{
	public:
		PickupComponent(BearBones::Entity* object);
		virtual ~PickupComponent() = default;

		PickupComponent(const PickupComponent& other) = delete;
		PickupComponent(PickupComponent&& other) = delete;
		PickupComponent& operator=(const PickupComponent& other) = delete;
		PickupComponent& operator=(PickupComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnPickup() = 0;
	};
}

#endif