#pragma once
#include <memory>
#include "Component.h"
//#include "Texture2D.h"


class Texture2D;

class TextureComponent final : public Component
{
public:
	TextureComponent(Entity* object);
	TextureComponent(Entity* object, const std::string& textureFile);

	virtual ~TextureComponent();
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;
	
	virtual void Update() override;
	virtual void Render() const override;
	virtual void RenderImGui() override;
	
	void SetTexture(const std::string& filename);

private:
	std::shared_ptr<Texture2D> m_pTexture{};
};



