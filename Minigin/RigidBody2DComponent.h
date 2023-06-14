// Inspired by Arne
#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H
#include "Component.h"
#include <functional>

namespace BearBones
{
	class RigidBody2DComponent : public Component
	{
		struct BoxCollider
		{
			float width;
			float height;
		};


	public:
		RigidBody2DComponent(Entity* object, const float width, const float height);

		~RigidBody2DComponent() override = default;
		RigidBody2DComponent(const RigidBody2DComponent& other) = delete;
		RigidBody2DComponent(RigidBody2DComponent&& other) = delete;
		RigidBody2DComponent& operator=(const RigidBody2DComponent& other) = delete;
		RigidBody2DComponent& operator=(RigidBody2DComponent&& other) = delete;

		virtual void Update() override {};
		virtual void Render() const override {};

		void SetOnCollisionEnterCallback(std::function<void(RigidBody2DComponent*)> callback) { m_OnCollisionEnterCallback = callback; }
		void SetOnCollisionExitCallback(std::function<void(RigidBody2DComponent*)> callback) { m_OnCollisionExitCallback = callback; }
		void SetOnCollisionCallback(std::function<void(RigidBody2DComponent*)> callback) { m_OnCollisionCallback = callback; }

		void OnCollisionEnter(RigidBody2DComponent* other) { if (m_OnCollisionEnterCallback) m_OnCollisionEnterCallback(other); }
		void OnCollisionExit(RigidBody2DComponent* other) { if (m_OnCollisionExitCallback) m_OnCollisionExitCallback(other); }
		void OnCollision(RigidBody2DComponent* other) { if (m_OnCollisionCallback) m_OnCollisionCallback(other); }

		BoxCollider GetCollider() const { return m_Collider; }

	private:
		BoxCollider m_Collider{};


		std::function<void(RigidBody2DComponent*)> m_OnCollisionEnterCallback{};
		std::function<void(RigidBody2DComponent*)> m_OnCollisionExitCallback{};
		std::function<void(RigidBody2DComponent*)> m_OnCollisionCallback{};
	};
}

#endif