#include "PookaComponent.h"
#include <ResourceManager.h>
#include <Renderer.h>
#include <Texture2D.h>
#include <TransformComponent.h>
#include <Entity.h>
#include <EngineTime.h>
#include "InflatableComponent.h"

DigDug::PookaComponent::PookaComponent(Entity* object)
	: Component(object)
	, m_idleTexture{ ResourceManager::GetInstance().LoadTexture("Resources/Sprites/Enemies/Pooka/Walk/0.png") }
{

	if (!GetOwner()->HasComponent<InflatableComponent>())
	{
		GetOwner()->AddComponent<InflatableComponent>();
	}
	auto inflateComp = GetOwner()->GetComponent<InflatableComponent>();
	inflateComp->RegisterObserver(this);


}

void DigDug::PookaComponent::Update()
{
	if (m_inflateIndex > 0)
	{
		m_deflateTimer += TIME.GetDeltaTime();
		if (m_deflateTimer > m_deflateInterval)
		{
			m_deflateTimer = 0.f;
			m_inflateIndex--;
		}
	}
}

void DigDug::PookaComponent::Render() const
{
	const auto pos = m_pOwner->GetTransform()->GetWorldPosition();
	glm::vec2 textureSize = m_idleTexture->GetSize();
	auto scale = m_pOwner->GetTransform()->GetWorldScale();
	textureSize *= scale;
	Renderer::GetInstance().RenderTexture(*m_idleTexture, pos.x, pos.y, textureSize.x, textureSize.y);
}

void DigDug::PookaComponent::OnNotify(Entity*)
{
	m_inflateIndex++;
}
