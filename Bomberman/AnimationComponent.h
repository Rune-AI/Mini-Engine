#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "SpriteComponent.h"
#include <string>
#include <memory>

namespace Bomberman
{
	class ControllerComponent;
	class Texture2D;

	struct AnimationData
	{
		int startIndex;
		int endIndex;
	};


	enum class AnimationState
	{
		Idle,
		Walk,
		Death
	};


	class AnimationComponent : public BearBones::SpriteComponent
	{
	public:
		AnimationComponent(BearBones::Entity* object, ControllerComponent* controller);
		AnimationComponent(BearBones::Entity* object, const std::string& textureFile, ControllerComponent* controller);
		AnimationComponent(BearBones::Entity* object, std::shared_ptr<BearBones::Texture2D> texture, ControllerComponent* controller);
		virtual ~AnimationComponent() = default;

		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void SetUpAnimation(const AnimationData& data);
		void SetDownAnimation(const AnimationData& data);
		void SetLeftAnimation(const AnimationData& data);
		void SetRightAnimation(const AnimationData& data);
		void SetDeathAnimation(const AnimationData& data);

	private:
		ControllerComponent* m_pController;
		AnimationState m_State{AnimationState::Idle};
		AnimationData m_UpAnimation{};
		AnimationData m_DownAnimation{};
		AnimationData m_LeftAnimation{};
		AnimationData m_RightAnimation{};
		AnimationData m_DeathAnimation{};

		void ApplyAnimationData(AnimationData data, bool isLooping);
	};
}

#endif