#include "FPSCounterComponent.h"
#include "ResourceManager.h"
#include "Time.h"
#include <format>

FPSCounterComponent::FPSCounterComponent(Entity* entity, std::shared_ptr<Font> font)
	: TextComponent(entity, " ", font)
{
}

void FPSCounterComponent::Update()
{
	float deltaTime = Time::GetInstance().GetDeltaTime();
	m_TimeSinceLastFPSPush += deltaTime;

	if (m_TimeSinceLastFPSPush >= 0.5f)
	{

		float FPS = 1.0f / deltaTime;
		SetText(std::format("{} FPS", std::to_string((int)FPS)));

		m_TimeSinceLastFPSPush = 0.f;
	}

	TextComponent::Update();
}

void FPSCounterComponent::Render() const
{
	TextComponent::Render();
}
