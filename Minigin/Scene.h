#ifndef SCENE_H
#define SCENE_H

#include "SceneManager.h"
#include "Entity.h"

namespace BearBones
{
	class Scene final //keep this final >:( more dynamic/open system
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		void Add(std::unique_ptr<Entity> object);
		void Remove(std::unique_ptr<Entity> object);
		void RemoveAll();

		void Update();
		void Render() const;
		void RenderImGui();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		bool GetIsActive() const { return IsActive; };
		void SetIsActive(bool value) { IsActive = value; };

		std::string GetName() const { return m_name; };

		Entity* GetCamera() const;

	private:
		bool IsActive{true};


		std::string m_name;
		std::vector <std::unique_ptr<Entity>> m_objects{};

		static unsigned int m_idCounter;
	};
}
#endif //SCENE_H