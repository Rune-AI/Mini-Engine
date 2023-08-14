#include "LevelComponent.h"

#include <SceneManager.h>
#include <ResourceManager.h>
#include <TextureComponent.h>
#include <Entity.h>
#include <Scene.h>
#include <TransformComponent.h>
#include <Texture2D.h>
#include <Renderer.h>
#include "Stage.h"

DigDug::LevelComponent::LevelComponent(BearBones::Entity* object, int sizeX, int sizeY)
	: Component{ object }
	, m_gridSize{ sizeX, sizeY }
{
	for (size_t i = 0; i < 6; i++)
	{
		m_groundTextures.emplace_back(BearBones::ResourceManager::GetInstance().LoadTexture(
			"Resources/Sprites/Level/" + std::to_string(i) + ".png"));
	}

	for (int i = 0; i < m_gridSize.x * m_gridSize.y; i++)
	{
		m_groundStates.emplace_back(0);
	}

}

DigDug::LevelComponent::LevelComponent(BearBones::Entity* object, const Stage stage)
	: Component{ object }
	, m_gridSize{ stage.cols, stage.rows }
{
	//get file count in folder
	std::string spritesFolder = "Resources/Sprites/Level/";


	for (size_t i = 0; i < 24; i++)
	{
		m_groundTextures.emplace_back(BearBones::ResourceManager::GetInstance().LoadTexture(
			spritesFolder + std::to_string(i) + ".png"));
	}

	for (int state : stage.groundStates)
	{
		m_groundStates.emplace_back(state);
	}

}

void DigDug::LevelComponent::Update()
{

}

void DigDug::LevelComponent::Render() const
{
	const auto topLeftPos = m_pOwner->GetTransform()->GetWorldPosition();
	glm::vec2 textureSize = m_groundTextures[0]->GetSize();
	auto scale = m_pOwner->GetTransform()->GetWorldScale();
	textureSize *= scale;

	for (int x = 0; x < m_gridSize.x; x++)
	{
		for (int y = 0; y < m_gridSize.y; y++)
		{
			const auto index = x + y * m_gridSize.x;
			const int textureState = m_groundStates[index];
			const auto offsetPos = glm::vec2{ x * textureSize.x, y * textureSize.y };
			const auto pos = topLeftPos + offsetPos;

			BearBones::Renderer::GetInstance().RenderTexture(*m_groundTextures[textureState], pos.x, pos.y, textureSize.x, textureSize.y);
		}
	}
	
}
