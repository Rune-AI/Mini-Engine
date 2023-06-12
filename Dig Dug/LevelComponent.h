#ifndef LEVEL_COMPONENT_H
#define LEVEL_COMPONENT_H

#include "Component.h"
#include <glm/ext/vector_int2.hpp>
#include <vector>
#include <memory>
#include <Texture2D.h>
#include "Stage.h"


namespace DigDug
{
	class LevelComponent : public Component
	{
	public:
		LevelComponent(Entity* object, int sizeX, int sizeY);
		LevelComponent(Entity* object, const Stage stage);
		virtual ~LevelComponent() = default;

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;


	private:
		glm::ivec2 m_gridSize;
		std::vector<std::shared_ptr<Texture2D>> m_groundTextures{};
		std::vector<int> m_groundStates{};
	};
}

#endif