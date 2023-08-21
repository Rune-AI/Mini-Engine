#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "ControllerComponent.h"
#include "BombCommand.h"

namespace Bomberman
{

	class PlayerController : public ControllerComponent
	{
	public:
		PlayerController(BearBones::Entity* object, BearBones::Entity* level);
		PlayerController(BearBones::Entity* object, BearBones::Entity* level, bool m_UseArrows, bool m_useWASD, bool m_UseController);
		virtual ~PlayerController() = default;

		PlayerController(const PlayerController& other) = delete;
		PlayerController(PlayerController&& other) = delete;
		PlayerController& operator=(const PlayerController& other) = delete;
		PlayerController& operator=(PlayerController&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void IncrementFlamePower();
		void IncrementBombCount();

		int GetFlamePower() const;
		int GetBombCount() const;

		void KillPlayer();
		bool IsDead() const;

		void SetUseArrows(bool useArrows);
		void SetUseWASD(bool useWASD);
		void SetUseController(bool useController);

	private:
		void HandleInput();
		int m_FlamePower{1};
		int m_BombCount{1};
		bool m_IsDead{false};
		bool m_UseArrows{true};
		bool m_UseWASD{true};
		bool m_UseController{true};

		BombCommand m_BombCommand;
		int m_CurrentBombCount{ 1 };
		float m_BombSpawnDelay{ 4.f };
		float m_BombSpawnTime{ 0.0f };
		void SpawnBomb();

	};
}

#endif