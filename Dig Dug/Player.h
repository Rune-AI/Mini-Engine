#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include <Component.h>

#include <memory>
#include <Texture2D.h>
#include <vector>

namespace DigDug
{
	class Player : public Component
	{
	public:
		Player(Entity* object);
		virtual ~Player() = default;

		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void OnPumpShoot();
	private:
		void Move();
		void HandleControllerInput();
		void HandleKeyboardInput();

		void UpdatePump();
		void RenderPump() const;
		void OnPumpHit();
		void OnPumpPulse();

		float m_pumpHeadDistance{};
		float m_pumpHeadSpeed{10.f};
		float m_pumpHeadMaxDistance{ 16.f * 3.f };
		float m_pumpPulseTime{};
		float m_pumpPulseInterval{};

		bool m_IsPumping{ false };
		bool m_IsPumpAttached{ false };
		bool m_IsDigging{ false };

		bool m_IsMovementButtonPressed{};
		glm::vec2 m_moveDirection {};
		float m_angle{};


		std::shared_ptr<Texture2D> m_idleTexture{};
		std::shared_ptr<Texture2D> m_pumpTexture{};
		std::shared_ptr<Texture2D> m_ropeTexture{};
	};
}

#endif