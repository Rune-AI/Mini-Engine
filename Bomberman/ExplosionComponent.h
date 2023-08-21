#ifndef EXPLOSION_COMPONENT_H
#define EXPLOSION_COMPONENT_H

#include "Component.h"

namespace Bomberman
{
	class ExplosionComponent : public BearBones::Component
	{
	public:
		ExplosionComponent(BearBones::Entity* object);
		virtual ~ExplosionComponent() = default;

		ExplosionComponent(const ExplosionComponent& other) = delete;
		ExplosionComponent(ExplosionComponent&& other) = delete;
		ExplosionComponent& operator=(const ExplosionComponent& other) = delete;
		ExplosionComponent& operator=(ExplosionComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		//virtual void OnTouch() {};
	};
}

#endif