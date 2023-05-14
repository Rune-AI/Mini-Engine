#pragma once
#include "TextComponent.h"
class FPSCounterComponent : public TextComponent
{
public:
	FPSCounterComponent(Entity* entity, std::shared_ptr<Font> font);
	virtual ~FPSCounterComponent() = default;

	FPSCounterComponent(const FPSCounterComponent& other) = delete;
	FPSCounterComponent(FPSCounterComponent&& other) = delete;
	FPSCounterComponent& operator=(const FPSCounterComponent& other) = delete;
	FPSCounterComponent& operator=(FPSCounterComponent&& other) = delete;

	virtual void Update() override;
	virtual void Render() const override;

private:
	float m_TimeSinceLastFPSPush{};
};

