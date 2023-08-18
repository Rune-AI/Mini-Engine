#ifndef WALL_COMPONENT_H
#define WALL_COMPONENT_H

#include "DestructableComponent.h"

namespace Bomberman
{
	class WallComponent final : public DestructableComponent
	{
	public:
		WallComponent(BearBones::Entity* object);
		virtual ~WallComponent() = default;

		WallComponent(const WallComponent& other) = delete;
		WallComponent(WallComponent&& other) = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnDestroy() override;
	};
}

#endif