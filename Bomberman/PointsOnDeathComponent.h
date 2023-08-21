#ifndef POINTS_COMPONENT_H
#define POINTS_COMPONENT_H

#include "DestructableComponent.h"

namespace Bomberman
{
	class LevelComponent;
	class PointsOnDeathComponent final : public DestructableComponent
	{
	public:
		PointsOnDeathComponent(BearBones::Entity* object, LevelComponent* level);
		virtual ~PointsOnDeathComponent() = default;

		PointsOnDeathComponent(const PointsOnDeathComponent& other) = delete;
		PointsOnDeathComponent(PointsOnDeathComponent&& other) = delete;
		PointsOnDeathComponent& operator=(const PointsOnDeathComponent& other) = delete;
		PointsOnDeathComponent& operator=(PointsOnDeathComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnNotify(int data) override;

	private:
		LevelComponent* m_pLevel;
	};
}

#endif