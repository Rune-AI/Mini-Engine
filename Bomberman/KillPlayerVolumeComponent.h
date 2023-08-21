#ifndef KILLPLAYER_COMPONENT_H
#define KILLPLAYER_COMPONENT_H

#include "TriggerComponent.h"
#include "LevelComponent.h"

namespace Bomberman
{
	class KillPlayerVolumeComponent : public Bomberman::TriggerComponent
	{
	public:
		KillPlayerVolumeComponent(BearBones::Entity* object, BearBones::Entity* Level);
		virtual ~KillPlayerVolumeComponent() = default;

		KillPlayerVolumeComponent(const KillPlayerVolumeComponent& other) = delete;
		KillPlayerVolumeComponent(KillPlayerVolumeComponent&& other) = delete;
		KillPlayerVolumeComponent& operator=(const KillPlayerVolumeComponent& other) = delete;
		KillPlayerVolumeComponent& operator=(KillPlayerVolumeComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnTouch(BearBones::Entity* other) override;

	private:
		LevelComponent* m_pLevel;
	};
}

#endif