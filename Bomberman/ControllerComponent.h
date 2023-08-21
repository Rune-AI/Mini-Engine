#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include "Component.h"

namespace Bomberman
{
	class LevelComponent;

	enum class Direction
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	class ControllerComponent : public BearBones::Component
	{
	public:
		ControllerComponent(BearBones::Entity* object, BearBones::Entity* level);
		virtual ~ControllerComponent() = default;

		ControllerComponent(const ControllerComponent& other) = delete;
		ControllerComponent(ControllerComponent&& other) = delete;
		ControllerComponent& operator=(const ControllerComponent& other) = delete;
		ControllerComponent& operator=(ControllerComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void Move(float x, float y);
		void Move(Direction direction);
		Direction GetDirection() const;

		void SetSpeed(float speed);

	protected:
		LevelComponent* m_pLevel;
		float m_Speed{1};
		Direction m_LastDirection{Direction::Down};
		float m_CollisionSize{ 16.f };
	};
}

#endif