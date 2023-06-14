#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <memory>
#include "Singleton.h"
#include <unordered_map>

namespace BearBones
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		std::string LoadSound(const std::string& file) const;

		void UnloadUnusedTextures();

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_LoadedTextures{};
	};
}

#endif //RESOURCE_MANAGER_H