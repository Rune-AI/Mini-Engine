#ifndef BOMB_COMPONENT_H
#define BOMB_COMPONENT_H

#include "DestructableComponent.h"
#include <Subject.h>

namespace Bomberman
{
	class LevelComponent;
	class BombComponent : public DestructableComponent, public BearBones::Subject<DestructableComponent*, int>
	{
	public:
		BombComponent(BearBones::Entity* object, LevelComponent* level, int range);
		virtual ~BombComponent() = default;

		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void OnNotify(int index) override;

	private:
		LevelComponent* m_pLevel;
		float m_BombTime{};
		float m_FuseTime{3.f};
		int m_Range{};
		bool m_IsExploding{ false };
		void Explode();

		void SpawnExplosion(float x, float y);
		bool CheckForWall(float x, float y);
	};
}

#endif