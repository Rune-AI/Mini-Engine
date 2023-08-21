#ifndef TRIGGER_COMPONENT_H
#define TRIGGER_COMPONENT_H

#include "Component.h"
#include <vector>

namespace Bomberman
{
	class TriggerComponent : public BearBones::Component
	{
	public:
		TriggerComponent(BearBones::Entity* object);
		virtual ~TriggerComponent() = default;

		TriggerComponent(const TriggerComponent& other) = delete;
		TriggerComponent(TriggerComponent&& other) = delete;
		TriggerComponent& operator=(const TriggerComponent& other) = delete;
		TriggerComponent& operator=(TriggerComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnTouch(BearBones::Entity* other) = 0;

		void AddObserver(BearBones::Entity* observer);
		void SetObservers(std::vector<BearBones::Entity*> observers);

	private:
		float triggerRange{14.f};
		std::vector<BearBones::Entity*> m_Observers;
	};
}

#endif