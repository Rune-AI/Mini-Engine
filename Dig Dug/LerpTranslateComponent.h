#ifndef LERP_TRANSLATE_COMPONENT_H
#define LERP_TRANSLATE_COMPONENT_H

#include "Component.h"
#include <glm/ext/vector_float2.hpp>

namespace DigDug
{
	class LerpTranslateComponent : public BearBones::Component
	{
	public:
		LerpTranslateComponent(BearBones::Entity* object, float destinationX, float destinationY, float lerpTime);
		virtual ~LerpTranslateComponent() = default;

		LerpTranslateComponent(const LerpTranslateComponent& other) = delete;
		LerpTranslateComponent(LerpTranslateComponent&& other) = delete;
		LerpTranslateComponent& operator=(const LerpTranslateComponent& other) = delete;
		LerpTranslateComponent& operator=(LerpTranslateComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override {};


	private:
		glm::vec2 m_destinationPos{};
		glm::vec2 m_originalPos{};
		float m_lerpTime{};
		float m_currentTime{};
	};
}

#endif