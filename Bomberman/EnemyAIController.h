#ifndef ENEMYAI_COMPONENT_H
#define ENEMYAI_COMPONENT_H

#include "ControllerComponent.h"

namespace Bomberman
{
	class EnemyAIController : public BombermanControllerComponent
	{
	public:
		EnemyAIController(BearBones::Entity* object);
		virtual ~EnemyAIController() = default;

		EnemyAIController(const EnemyAIController& other) = delete;
		EnemyAIController(EnemyAIController&& other) = delete;
		EnemyAIController& operator=(const EnemyAIController& other) = delete;
		EnemyAIController& operator=(EnemyAIController&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override = 0;

		virtual void OnPickup() = 0;

	private:
		int m_Smart;
		int m_Speed;
		int m_Points;
	};
}

#endif