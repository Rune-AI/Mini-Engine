#ifndef FYGAR_COMPONENT_H
#define FYGAR_COMPONENT_H

#include <Component.h>

namespace DigDug
{
	class FygarComponent : public BearBones::Component
	{
	public:
		FygarComponent(BearBones::Entity* object);
		virtual ~FygarComponent() = default;

		FygarComponent(const FygarComponent& other) = delete;
		FygarComponent(FygarComponent&& other) = delete;
		FygarComponent& operator=(const FygarComponent& other) = delete;
		FygarComponent& operator=(FygarComponent&& other) = delete;

		virtual void Update() override {};
		virtual void Render() const override {};

	private:

	};
}

#endif