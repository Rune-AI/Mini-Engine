#pragma once
#include <SDL.h>
#include "Singleton.h"

#define RENDERER Renderer::GetInstance()

class Texture2D;
/**
	* Simple RAII wrapper for the SDL renderer
	*/
class Renderer final : public Singleton<Renderer>
{
	SDL_Renderer* m_renderer{};
	SDL_Window* m_window{};
	SDL_Color m_clearColor{};	
public:
	void Init(SDL_Window* window);
	void Render();
	void RenderImGui();
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
	void RenderTextureEx(const Texture2D& texture, const float x, const float y, const float angle, const SDL_RendererFlip flip) const;
	void RenderTextureEx(const Texture2D& texture, const float x, const float y, const float width, const float height, const float angle, const SDL_RendererFlip flip) const;
	void RenderTextureEx(const Texture2D& texture, const float x, const float y, const float angle, const SDL_RendererFlip flip, const float scaleX, const float scaleY) const;

	SDL_Renderer* GetSDLRenderer() const;

	const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
};

