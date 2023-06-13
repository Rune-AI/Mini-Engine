#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Entity.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file)
{
	// unload any unused textures, we assume this function gets called when textures are being swapped, or the level is being loaded. So the poeration can take some time
	// this function is not called every frame, so it's fine to do this here
	UnloadUnusedTextures();

	const auto fullPath = m_dataPath + file;

	//check if texture is already loaded
	auto it = m_LoadedTextures.find(fullPath);
	if (it != m_LoadedTextures.end())
	{
		//if found, return it
		return it->second;
	}

	// not found, load it
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	//add to loaded textures
	m_LoadedTextures[fullPath] = std::make_shared<Texture2D>(texture);

	return m_LoadedTextures[fullPath];
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}

std::string ResourceManager::LoadSound(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	return fullPath;
}

void ResourceManager::UnloadUnusedTextures()
{
	for (auto it = m_LoadedTextures.begin(); it != m_LoadedTextures.end();)
	{
		if (it->second.use_count() <= 1)
		{
			it = m_LoadedTextures.erase(it);
		}
		else
		{
			++it;
		}
	}
}