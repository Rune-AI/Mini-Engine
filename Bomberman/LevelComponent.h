#ifndef LEVEL_COMPONENT_H
#define LEVEL_COMPONENT_H

#include "Component.h"
#include <glm/ext/vector_int2.hpp>
#include <vector>
#include <memory>

namespace Bomberman
{
	class LevelComponent final : public BearBones::Component
	{
	public:
		LevelComponent(BearBones::Entity* object, int sizeX, int sizeY);
		virtual ~LevelComponent() = default;

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

	private:
		glm::ivec2 m_gridSize;
		std::vector<int> m_groundStates{};
	};
}

#endif