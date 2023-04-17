#include "ScoreComponent.h"

ScoreComponent::ScoreComponent(Entity* entity)
	:Component{ entity }
{
}

ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::Update()
{
}

void ScoreComponent::Render() const
{
}

void ScoreComponent::SetScore(int score)
{
	m_Score = score;
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}

void ScoreComponent::AddScore(int score)
{
	m_Score += score;
	NotifyObservers(m_Score);
}
