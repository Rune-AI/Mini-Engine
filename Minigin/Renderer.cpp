#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Scene.h"
#include "Entity.h"

#include "imgui.h"
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl2.h>
#include "TransformComponent.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void BearBones::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void BearBones::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	RenderImGui();
	
	SDL_RenderPresent(m_renderer);
}

void BearBones::Renderer::RenderImGui()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	
	SceneManager::GetInstance().RenderImGui();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void BearBones::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void BearBones::Renderer::RenderCopy(const Texture2D& texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) const
{
	auto camdstrect = *dstrect;
	WorldToCamera(camdstrect);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), srcrect, &camdstrect);
}

void BearBones::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	WorldToCamera(dst);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void BearBones::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	WorldToCamera(dst);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void BearBones::Renderer::RenderTextureEx(const Texture2D& texture, const float x, const float y, const float angle, const SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	WorldToCamera(dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, double(angle), nullptr, flip);
}

void BearBones::Renderer::RenderTextureEx(const Texture2D& texture, const float x, const float y, const float width, const float height, const float angle, const SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	WorldToCamera(dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, double(angle), nullptr, flip);
}

void BearBones::Renderer::RenderTextureEx(const Texture2D& texture, const float x, const float y, const float angle, const SDL_RendererFlip flip, const float scaleX, const float scaleY) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w = static_cast<int>(dst.w * scaleX);
	dst.h = static_cast<int>(dst.h * scaleY);
	WorldToCamera(dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, double(angle), nullptr, flip);
}

inline SDL_Renderer* BearBones::Renderer::GetSDLRenderer() const { return m_renderer; }

void BearBones::Renderer::WorldToCamera(SDL_Rect& rect) const
{
	const auto& camera = SceneManager::GetInstance().GetActiveScene()->GetCamera();
	if(camera == nullptr)
		return;
	auto camPos = camera->GetTransform()->GetWorldPosition();
	auto camScale = camera->GetTransform()->GetWorldScale();
	//auto camRotation = camera->GetTransform()->GetWorldRotation();

	rect.x -= int(camPos.x);
	rect.y -= int(camPos.y);

	rect.x = int(rect.x * camScale.x);
	rect.y = int(rect.y * camScale.y);
	rect.w = int(rect.w * camScale.x);
	rect.h = int(rect.h * camScale.y);


}
