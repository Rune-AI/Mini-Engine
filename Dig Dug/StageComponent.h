#ifndef STAGE_COMPONENT_H
#define STAGE_COMPONENT_H

#include "Component.h"
#include <memory>
#include <Texture2D.h>
#include <vector>


namespace DigDug
{
	struct Tile
	{
		bool isDug{false};
	};


	class StageComponent : public BearBones::Component
	{
	public:
		StageComponent(BearBones::Entity* object);
		virtual ~StageComponent() = default;

		StageComponent(const StageComponent& other) = delete;
		StageComponent(StageComponent&& other) = delete;
		StageComponent& operator=(const StageComponent& other) = delete;
		StageComponent& operator=(StageComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;


	private:
		std::shared_ptr<BearBones::Texture2D> m_pBackgroundTexture;
		std::vector<Tile> m_Tiles;

	};
}

#endif