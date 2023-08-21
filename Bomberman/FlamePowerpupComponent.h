#ifndef FLAME_COMPONENT_H
#define FLAME_COMPONENT_H

#include "TriggerComponent.h"
#include "LevelComponent.h"

namespace Bomberman
{
	class FlamePowerpupComponent : public Bomberman::TriggerComponent
	{
	public:
		FlamePowerpupComponent(BearBones::Entity* object);
		virtual ~FlamePowerpupComponent() = default;

		FlamePowerpupComponent(const FlamePowerpupComponent& other) = delete;
		FlamePowerpupComponent(FlamePowerpupComponent&& other) = delete;
		FlamePowerpupComponent& operator=(const FlamePowerpupComponent& other) = delete;
		FlamePowerpupComponent& operator=(FlamePowerpupComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnTouch(BearBones::Entity* other) override;
	};
}

#endif