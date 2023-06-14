#include <string>
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Renderer.h"

BearBones::TextureComponent::TextureComponent(Entity* object)
	: Component{ object }
{
}

BearBones::TextureComponent::TextureComponent(Entity* object, const std::string& textureFile)
	: Component{ object },
	m_pTexture{ ResourceManager::GetInstance().LoadTexture(textureFile) }
{
}

BearBones::TextureComponent::TextureComponent(Entity* object, std::shared_ptr<Texture2D> texture)
: Component{ object },
	m_pTexture{ texture }
{
}

BearBones::TextureComponent::~TextureComponent()
{
}

void BearBones::TextureComponent::Update()
{
}

void BearBones::TextureComponent::Render() const
{
	/*const auto& pos = m_pOwner->GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);*/


    const auto pos = m_pOwner->GetTransform()->GetWorldPosition();
    const auto scale = m_pOwner->GetTransform()->GetWorldScale();
    glm::vec2 textureSize = m_pTexture->GetSize();
    textureSize *= scale;


    Renderer::GetInstance().RenderTexture(*m_pTexture,
        pos.x, pos.y,
        float(textureSize.x), float(textureSize.y));


}

void BearBones::TextureComponent::RenderImGui()
{
}

void BearBones::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}