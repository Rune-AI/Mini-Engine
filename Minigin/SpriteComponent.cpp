#include "SpriteComponent.h"



#include <string>
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "EngineTime.h"

BearBones::SpriteComponent::SpriteComponent(Entity* object)
	: TextureComponent{ object }
{
}

BearBones::SpriteComponent::SpriteComponent(Entity* object, const std::string& textureFile)
	: TextureComponent{ object, textureFile }
{
}

BearBones::SpriteComponent::SpriteComponent(Entity* object, std::shared_ptr<Texture2D> texture)
	: TextureComponent{ object, texture }
{
}

BearBones::SpriteComponent::~SpriteComponent()
{
}

void BearBones::SpriteComponent::Update()
{
	if (m_IsPlaying)
	{
		m_SpriteTime += TIME.GetDeltaTime();

		if (m_SpriteTime > m_SpriteTimePerFrame)
		{
			m_SpriteTime -= m_SpriteTimePerFrame;
			++m_CurrentSpriteIndex;
			if (m_CurrentSpriteIndex > m_SpriteIndexEnd - m_SpriteIndexStart && !m_IsLooping)
			{
				m_IsCompleted = true;
				m_IsPlaying = false;
			}
			else
			{
				m_CurrentSpriteIndex = m_CurrentSpriteIndex % (m_SpriteIndexEnd - m_SpriteIndexStart);
			}
		}
	}
}

void BearBones::SpriteComponent::Render() const
{
	const auto pos = m_pOwner->GetTransform()->GetWorldPosition();
	const auto scale = m_pOwner->GetTransform()->GetWorldScale();
	glm::ivec2 textureSize = m_pTexture->GetSize();

	int index = m_CurrentSpriteIndex + m_SpriteIndexStart;
	SDL_Rect srcRect;
	srcRect.x = index * m_SpriteWidth % textureSize.x;
	srcRect.y = index * m_SpriteWidth / textureSize.x * m_SpriteHeight;
	srcRect.w = m_SpriteWidth;
	srcRect.h = m_SpriteHeight;

	SDL_Rect dstRect;
	dstRect.x = int(pos.x);
	dstRect.y = int(pos.y);
	dstRect.w = int(m_SpriteWidth * scale.x);
	dstRect.h = int(m_SpriteHeight * scale.y);

	Renderer::GetInstance().RenderCopy(*m_pTexture, &srcRect, &dstRect);
}

void BearBones::SpriteComponent::RenderImGui()
{
}

bool BearBones::SpriteComponent::GetIsCompleted() const
{
	return m_IsCompleted;
}

void BearBones::SpriteComponent::SetSpriteWidth(int width)
{
	m_SpriteWidth = width;
}

void BearBones::SpriteComponent::SetSpriteHeight(int height)
{
	m_SpriteHeight = height;
}

void BearBones::SpriteComponent::SetSpriteIndexStart(int index)
{
	m_SpriteIndexStart = index;
}

void BearBones::SpriteComponent::SetSpriteIndexEnd(int index)
{
	m_SpriteIndexEnd = index;
}

void BearBones::SpriteComponent::SetSpriteTimePerFrame(float time)
{
	m_SpriteTimePerFrame = time;
}

void BearBones::SpriteComponent::SetIsLooping(bool isLooping)
{
	m_IsLooping = isLooping;
}

void BearBones::SpriteComponent::SetIsPlaying(bool isPlaying)
{
	m_IsPlaying = isPlaying;
}


