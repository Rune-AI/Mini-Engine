#ifndef INFLATABLE_COMPONENT_H
#define INFLATABLE_COMPONENT_H

#include <Component.h>
#include <Subject.h>

namespace DigDug
{
	class InflatableComponent : public Component, public Subject<Entity*>
	{
	public:
		InflatableComponent(Entity* object);
		virtual ~InflatableComponent() = default;

		InflatableComponent(const InflatableComponent& other) = delete;
		InflatableComponent(InflatableComponent&& other) = delete;
		InflatableComponent& operator=(const InflatableComponent& other) = delete;
		InflatableComponent& operator=(InflatableComponent&& other) = delete;

		virtual void Update() override {};
		virtual void Render() const override {};

	private:
		



	};
}

#endif