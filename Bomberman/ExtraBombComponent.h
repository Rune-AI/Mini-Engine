#ifndef EXTRA_COMPONENT_H
#define EXTRA_COMPONENT_H

#include "TriggerComponent.h"
#include "LevelComponent.h"

namespace Bomberman
{
	class ExtraBombComponent : public Bomberman::TriggerComponent
	{
	public:
		ExtraBombComponent(BearBones::Entity* object);
		virtual ~ExtraBombComponent() = default;

		ExtraBombComponent(const ExtraBombComponent& other) = delete;
		ExtraBombComponent(ExtraBombComponent&& other) = delete;
		ExtraBombComponent& operator=(const ExtraBombComponent& other) = delete;
		ExtraBombComponent& operator=(ExtraBombComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnTouch(BearBones::Entity* other) override;
	};
}

#endif