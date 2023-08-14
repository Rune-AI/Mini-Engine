#include "TrailComponent.h"

#include <ResourceManager.h>
#include <Renderer.h>

DigDug::TrailComponent::TrailComponent(BearBones::Entity* object, std::string TunnelMaskTexturePath)
	: Component{ object }
	, m_pTunnelMaskTexture{ BearBones::ResourceManager::GetInstance().LoadTexture(TunnelMaskTexturePath)}
	, m_trailPositions{}
	, m_trailAngles{}
{
	m_trailAngles.reserve(50);
	m_trailPositions.reserve(50);
}

void DigDug::TrailComponent::Update()
{
}

void DigDug::TrailComponent::Render() const
{
	for (size_t i = 0; i < m_trailPositions.size(); i++)
	{
		BearBones::RENDERER.RenderTextureEx(*m_pTunnelMaskTexture, m_trailPositions[i].x, m_trailPositions[i].y, m_trailAngles[i], SDL_FLIP_NONE);
	}
}

void DigDug::TrailComponent::SpawnTrail(glm::vec2 position, float angle)
{
	m_trailPositions.emplace_back(position);
	m_trailAngles.emplace_back(angle);
}
