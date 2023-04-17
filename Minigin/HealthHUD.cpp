#include "HealthHUD.h"
#include "Entity.h"

#include "EventManager.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include <format>

HealthHUD::HealthHUD(Entity* entity, int health)
	: TextComponent(entity, std::format("Lives {}", health), ResourceManager::GetInstance().LoadFont("Lingua.otf", 16))
{
}

void HealthHUD::Update()
{
	TextComponent::Update();
}

void HealthHUD::Render() const
{
	TextComponent::Render();
}

void HealthHUD::OnNotify(int data)
{
	SetText(std::format("Lives {}", data));
}