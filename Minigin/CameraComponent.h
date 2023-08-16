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

	private:


	};
}

#endif //TEXTURE_COMPONENT_H
