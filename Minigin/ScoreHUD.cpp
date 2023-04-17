#include "ScoreHUD.h"
#include "Entity.h"

#include "EventManager.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include <format>

ScoreHUD::ScoreHUD(Entity* entity, int score)
	: TextComponent(entity, std::format("Score {}", score), ResourceManager::GetInstance().LoadFont("Lingua.otf", 16))
{
}

void ScoreHUD::Update()
{
	TextComponent::Update();
}

void ScoreHUD::Render() const
{
	TextComponent::Render();
}

void ScoreHUD::OnNotify(int data)
{
	SetText(std::format("Score {}", data));
}