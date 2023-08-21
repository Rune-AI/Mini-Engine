#ifndef DEBUG_COMPONENT_H
#define DEBUG_COMPONENT_H

#include "Component.h"

namespace Bomberman
{
	class DebugComponent : public BearBones::Component
	{
	public:
		DebugComponent(BearBones::Entity* object);
		virtual ~DebugComponent() = default;

		DebugComponent(const DebugComponent& other) = delete;
		DebugComponent(DebugComponent&& other) = delete;
		DebugComponent& operator=(const DebugComponent& other) = delete;
		DebugComponent& operator=(DebugComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;
	};
}

#endif