#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include "Component.h"

namespace Bomberman
{
	class MenuComponent : public BearBones::Component
	{
	public:
		MenuComponent(BearBones::Entity* object);
		virtual ~MenuComponent() = default;

		MenuComponent(const MenuComponent& other) = delete;
		MenuComponent(MenuComponent&& other) = delete;
		MenuComponent& operator=(const MenuComponent& other) = delete;
		MenuComponent& operator=(MenuComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;
	};
}

#endif