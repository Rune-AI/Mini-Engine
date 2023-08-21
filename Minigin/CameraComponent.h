#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include <memory>
#include <string>
#include "Component.h"

namespace BearBones
{
	class CameraComponent final : public Component
	{
	public:
		CameraComponent(Entity* object);

		virtual ~CameraComponent() override = default;
		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;
		virtual void RenderImGui() override;

		void SetTarget(Entity* target);

	private:
		Entity* m_pTarget{ nullptr };
		float m_MaxX{ 496.f };
		float m_MaxY{ 0.f };
		float m_MinX{ 0.f };
		float m_MinY{ 0.f };

		float m_OffsetX{ -100.f };

		float m_Lerp{ 1.f };

	};
}

#endif //TEXTURE_COMPONENT_H
