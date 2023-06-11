#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include <Component.h>

#include <memory>
#include <Texture2D.h>

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
		virtual void Render() const override {};

		void Pump();

	private:
		void OnPumpHit();


		bool m_IsPumping{ false };
		bool m_IsDigging{ false };

		std::shared_ptr<Texture2D> m_PumpTexture{};
		std::shared_ptr<Texture2D> m_RopeTexture{};
	};
}

#endif