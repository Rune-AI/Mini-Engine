#pragma once
#include <string>
#include <memory>
#include "Component.h"

class Font;
class Texture2D;

class TextComponent final : public Component
{
public:
	TextComponent(Entity* object, const std::string& text, std::shared_ptr<Font> font);
	
	~TextComponent() override = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update() override;
	virtual void Render() const override;
	virtual void RenderImGui() override;

	void SetText(const std::string& text);
	void SetPosition(float x, float y);

private:
	bool m_needsUpdate;
	std::string m_text;
	std::shared_ptr<Font> m_font;
	std::shared_ptr<Texture2D> m_textTexture;
};

