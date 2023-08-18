#ifndef PICKUP_COMPONENT_H
#define PICKUP_COMPONENT_H

#include "Component.h"
#include <Entity.h>

namespace Bomberman
{
	class ControllerComponent : public BearBones::Component
	{
	public:
		ControllerComponent(BearBones::Entity* object);
		virtual ~ControllerComponent() = default;

		ControllerComponent(const ControllerComponent& other) = delete;
		ControllerComponent(ControllerComponent&& other) = delete;
		ControllerComponent& operator=(const ControllerComponent& other) = delete;
		ControllerComponent& operator=(ControllerComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

	private:
		BearBones::Entity* m_pLevel;
	};
}

#endif