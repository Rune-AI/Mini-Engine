#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include <glm/ext/vector_float2.hpp>

namespace BearBones
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(Entity* pOwner);
		TransformComponent(Entity* pOwner, glm::vec2 position, float rotation, glm::vec2 scale);

		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;
		virtual void RenderImGui() override;


		void SetDirty();
		// Position
		void SetWorldPosition(const glm::vec2& position);
		void SetWorldPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& position);
		void SetLocalPosition(float x, float y);
		void SetPositionDirty();
	
		const glm::vec2& GetWorldPosition();
		const glm::vec2& GetLocalPosition() const;

		// Rotation
		void SetWorldRotation(float rotation);
		void SetLocalRotation(float rotation);
		void SetRotationDirty();
	
		float GetWorldRotation();
		float GetLocalRotation() const;

		// Scale
		void SetWorldScale(const glm::vec2& scale);
		void SetWorldScale(float x, float y);
		void SetLocalScale(const glm::vec2& scale);
		void SetLocalScale(float x, float y);
		void SetScaleDirty();
	
		const glm::vec2& GetWorldScale();
		const glm::vec2& GetLocalScale() const;
	
	private:
		void UpdateWorldPosition();
		void UpdateWorldRotation();
		void UpdateWorldScale();
		void UpdateWorldTransform();

		glm::vec2 m_worldPosition{};
		glm::vec2 m_localPosition{};
		float m_worldRotation{};
		float m_localRotation{};
		glm::vec2 m_worldScale{ 1.f,1.f };
		glm::vec2 m_localScale{ 1.f,1.f };
		bool m_positionDirty{ true };
		bool m_rotationDirty{ true };
		bool m_scaleDirty{ true };
	};
}
#endif //TRANSFORM_COMPONENT_H