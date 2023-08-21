#ifndef DESTRUCTABLE_COMPONENT_H
#define DESTRUCTABLE_COMPONENT_H

#include "Component.h"
#include <IObserver.h>

namespace Bomberman
{
	class DestructableComponent : public BearBones::Component, public BearBones::IObserver<DestructableComponent*, int>
	{
	public:
		DestructableComponent(BearBones::Entity* object);
		virtual ~DestructableComponent() = default;

		DestructableComponent(const DestructableComponent& other) = delete;
		DestructableComponent(DestructableComponent&& other) = delete;
		DestructableComponent& operator=(const DestructableComponent& other) = delete;
		DestructableComponent& operator=(DestructableComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnNotify(int data) = 0;
		virtual IObserver<DestructableComponent*, int>* GetObserver() { return this; };
	};
}

#endif