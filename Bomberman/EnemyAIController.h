#ifndef ENEMYAI_COMPONENT_H
#define ENEMYAI_COMPONENT_H

#include "ControllerComponent.h"

namespace Bomberman
{
	enum class Intelligence
	{
		Dumb,
		Smart
	};

	class EnemyAIController : public ControllerComponent
	{
	public:
		EnemyAIController(BearBones::Entity* object, BearBones::Entity* level);
		virtual ~EnemyAIController() = default;

		EnemyAIController(const EnemyAIController& other) = delete;
		EnemyAIController(EnemyAIController&& other) = delete;
		EnemyAIController& operator=(const EnemyAIController& other) = delete;
		EnemyAIController& operator=(EnemyAIController&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void SetIntelligence(Intelligence intelligence);

	private:
		Intelligence m_Intelligence{ Intelligence::Dumb };
		int m_Points{100};
		int m_LastIndex{};
	};
}

#endif