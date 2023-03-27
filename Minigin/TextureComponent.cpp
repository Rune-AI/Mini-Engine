#include <string>
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Renderer.h"

TextureComponent::TextureComponent(Entity* object)
	: Component{ object }
{
}

TextureComponent::TextureComponent(Entity* object, const std::string& textureFile)
	: Component{ object },
	m_pTexture{ ResourceManager::GetInstance().LoadTexture(textureFile) }
{
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Update()
{
}

void TextureComponent::Render() const
{
	const auto& pos = m_pOwner->GetTransform()->GetLocalPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void TextureComponent::RenderImGui()
{
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}