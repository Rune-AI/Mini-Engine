#ifndef TRAIL_COMPONENT_H
#define TRAIL_COMPONENT_H

#include "Component.h"
#include <memory>
#include <Texture2D.h>
#include <string>
#include <vector>


namespace DigDug
{
	class TrailComponent : public BearBones::Component
	{
	public:
		TrailComponent(BearBones::Entity* object, std::string TunnelMaskTexture);
		virtual ~TrailComponent() = default;

		TrailComponent(const TrailComponent& other) = delete;
		TrailComponent(TrailComponent&& other) = delete;
		TrailComponent& operator=(const TrailComponent& other) = delete;
		TrailComponent& operator=(TrailComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;
		
		void SpawnTrail(glm::vec2 position, float angle);


	private:
		std::shared_ptr<BearBones::Texture2D> m_pTunnelMaskTexture;
		std::vector<glm::vec2> m_trailPositions{};
		std::vector<float> m_trailAngles{};
	};
}

#endif