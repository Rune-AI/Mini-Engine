#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "Texture2D.h"

class TextureComponent final : public Component
{
public:
	TextureComponent(Entity* object);
	TextureComponent(Entity* object, const std::string& textureFile);
	TextureComponent(Entity* object, std::shared_ptr<Texture2D> texture);

	virtual ~TextureComponent();
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;
	
	virtual void Update() override;
	virtual void Render() const override;
	virtual void RenderImGui() override;
	
	void SetTexture(const std::string& filename);
	glm::ivec2 GetTextureSize() const { return m_pTexture->GetSize(); }

private:
	std::shared_ptr<Texture2D> m_pTexture{};
};



