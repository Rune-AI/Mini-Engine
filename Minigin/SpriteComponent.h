#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <memory>
#include <string>
#include "TextureComponent.h"
#include "Texture2D.h"

namespace BearBones
{
	class SpriteComponent final : public TextureComponent
	{
	public:
		SpriteComponent(Entity* object);
		SpriteComponent(Entity* object, const std::string& textureFile);
		SpriteComponent(Entity* object, std::shared_ptr<Texture2D> texture);

		virtual ~SpriteComponent();
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;
		virtual void RenderImGui() override;

		bool GetIsCompleted() const;

		void SetSpriteWidth(int width);
		void SetSpriteHeight(int height);
		void SetSpriteIndexStart(int index);
		void SetSpriteIndexEnd(int index);
		void SetSpriteTimePerFrame(float time);
		void SetIsLooping(bool isLooping);
		void SetIsPlaying(bool isPlaying);

	private:
		int m_SpriteWidth{16};
		int m_SpriteHeight{16};
		int m_SpriteIndexStart{};
		int m_SpriteIndexEnd{};
		int m_CurrentSpriteIndex{};
		float m_SpriteTime{};
		float m_SpriteTimePerFrame{};
		bool m_IsLooping{};
		bool m_IsPlaying{};
		bool m_IsCompleted{};

	};
}

#endif //SPRITE_COMPONENT_H
