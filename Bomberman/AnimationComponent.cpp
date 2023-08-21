#include "AnimationComponent.h"
#include "ControllerComponent.h"

Bomberman::AnimationComponent::AnimationComponent(BearBones::Entity* object, ControllerComponent* controller)
	: SpriteComponent{ object },
	m_pController{ controller }
{
}

Bomberman::AnimationComponent::AnimationComponent(BearBones::Entity* object, const std::string& textureFile, ControllerComponent* controller)
: SpriteComponent{ object, textureFile },
	m_pController{ controller }
{
}

Bomberman::AnimationComponent::AnimationComponent(BearBones::Entity* object, std::shared_ptr<BearBones::Texture2D> texture, ControllerComponent* controller)
	: SpriteComponent{ object, texture },
	m_pController{ controller }
{
}

void Bomberman::AnimationComponent::Update()
{
	if (m_State == AnimationState::Death)
	{
		return;
	}

	auto direction = m_pController->GetDirection();
	switch (direction)
	{
	case Bomberman::Direction::None:
		m_State = AnimationState::Idle;
		SpriteComponent::SetIsPlaying(false);
		break;
	case Bomberman::Direction::Up:
		ApplyAnimationData(m_UpAnimation, true);
		m_State = AnimationState::Walk;
	case Bomberman::Direction::Down:
		ApplyAnimationData(m_DownAnimation, true);
		m_State = AnimationState::Walk;
	case Bomberman::Direction::Left:
		ApplyAnimationData(m_LeftAnimation, true);
		m_State = AnimationState::Walk;
	case Bomberman::Direction::Right:
		ApplyAnimationData(m_RightAnimation, true);
		m_State = AnimationState::Walk;
		//set current animation data to right and set index correctly
		break;
	default:
		break;
	}


	SpriteComponent::Update();

}

void Bomberman::AnimationComponent::Render() const
{
	SpriteComponent::Render();
}

void Bomberman::AnimationComponent::SetUpAnimation(const AnimationData& data)
{
	m_UpAnimation = data;
}

void Bomberman::AnimationComponent::SetDownAnimation(const AnimationData& data)
{
	m_DownAnimation = data;
}

void Bomberman::AnimationComponent::SetLeftAnimation(const AnimationData& data)
{
	m_LeftAnimation = data;
}


void Bomberman::AnimationComponent::SetRightAnimation(const AnimationData& data)
{
	m_RightAnimation = data;
}

void Bomberman::AnimationComponent::SetDeathAnimation(const AnimationData& data)
{
	m_DeathAnimation = data;
}

void Bomberman::AnimationComponent::ApplyAnimationData(AnimationData data, bool isLooping)
{
	SpriteComponent::SetSpriteIndexStart(data.startIndex);
	SpriteComponent::SetSpriteIndexEnd(data.endIndex);
	SpriteComponent::SetIsLooping(isLooping);
	SpriteComponent::SetIsPlaying(true);

}
