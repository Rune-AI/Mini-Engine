#ifndef KILL_COMPONENT_H
#define KILL_COMPONENT_H

#include "TriggerComponent.h"
#include "LevelComponent.h"

namespace Bomberman
{
	class KillVolumeComponent : public Bomberman::TriggerComponent
	{
	public:
		KillVolumeComponent(BearBones::Entity* object, BearBones::Entity* Level);
		virtual ~KillVolumeComponent() = default;

		KillVolumeComponent(const KillVolumeComponent& other) = delete;
		KillVolumeComponent(KillVolumeComponent&& other) = delete;
		KillVolumeComponent& operator=(const KillVolumeComponent& other) = delete;
		KillVolumeComponent& operator=(KillVolumeComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnTouch(BearBones::Entity* other) override;

	private:
		LevelComponent* m_pLevel;
	};
}

#endif