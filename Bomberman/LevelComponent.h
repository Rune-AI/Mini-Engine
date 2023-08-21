#ifndef LEVEL_COMPONENT_H
#define LEVEL_COMPONENT_H

#include "Component.h"
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <memory>

namespace Bomberman
{
	class DestructableComponent;
	class TriggerComponent;
	enum class GroundState
	{
		Solid,
		Empty,
		Wall,
		Bomb
	};

	class LevelComponent final : public BearBones::Component
	{
	public:
		LevelComponent(BearBones::Entity* object, int sizeX, int sizeY);
		virtual ~LevelComponent() = default;

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		int GetIndexAtPos(float x, float y) const;
		GroundState GetGroundStateAtPos(float x, float y) const;
		GroundState GetGroundStateAtIndex(int index) const;
		void SetGroundStateAtPos(float x, float y, GroundState state);
		void SetGroundStateAtIndex(int index, GroundState state);
		int GetLevelSizeX() const;
		int GetLevelSizeY() const;
		int GetTileSize() const;
		glm::vec2 GetPosAtIndex(int index) const;

		void ExplodeAtPos(float x, float y);

		std::vector<DestructableComponent*> GetDestructibles() const;
		void AddDestructible(DestructableComponent* destructible);

		void AddPlayer(BearBones::Entity* player);
		void GetPlayers(std::vector<BearBones::Entity*>& players) const;
		void GetEnemies(std::vector<BearBones::Entity*>& enemies) const;

		void SpawnEnemies();
		void SetTriggers();

		void CheckGameOver();

	private:
		glm::ivec2 m_gridSize;
		std::vector<GroundState> m_groundStates{};
		std::vector<DestructableComponent*> m_Destructibles{};
		std::vector<BearBones::Entity*> m_Players{};
		std::vector<BearBones::Entity*> m_Enemies{};
		std::vector<TriggerComponent*> m_Triggers{};
		int m_TileSize{ 16 };


		
		int m_EnemySpawnChance{ 5 };
		void SpawnRandomEnemy(int index);

		
	};
}

#endif