#ifndef TRIGGER_COMPONENT_H
#define TRIGGER_COMPONENT_H

#include "Component.h"

namespace Bomberman
{
	class TriggerComponent : public BearBones::Component
	{
	public:
		TriggerComponent(BearBones::Entity* object);
		virtual ~TriggerComponent() = default;

		TriggerComponent(const TriggerComponent& other) = delete;
		TriggerComponent(TriggerComponent&& other) = delete;
		TriggerComponent& operator=(const TriggerComponent& other) = delete;
		TriggerComponent& operator=(TriggerComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnPickup() = 0;
	};
}

#endif