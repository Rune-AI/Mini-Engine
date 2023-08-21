#ifndef DOOR_COMPONENT_H
#define DOOR_COMPONENT_H

#include "TriggerComponent.h"
#include "LevelComponent.h"

namespace Bomberman
{
	class DoorComponent : public Bomberman::TriggerComponent
	{
	public:
		DoorComponent(BearBones::Entity* object, BearBones::Entity* Level);
		virtual ~DoorComponent() = default;

		DoorComponent(const DoorComponent& other) = delete;
		DoorComponent(DoorComponent&& other) = delete;
		DoorComponent& operator=(const DoorComponent& other) = delete;
		DoorComponent& operator=(DoorComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnTouch(BearBones::Entity* other) override;

	private:
		LevelComponent* m_pLevel;
	};
}

#endif