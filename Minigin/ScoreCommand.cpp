#include "ScoreCommand.h"
#include "Entity.h"
#include "ScoreComponent.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4389)
#include "CSteamAchievements.h"
#pragma warning(pop)

void ScoreCommand::Execute()
{
	auto scoreComponent = m_Entity->GetComponent<ScoreComponent>();
	scoreComponent->AddScore(1);

	CSteamAchievements::GetInstance().SetAchievement("ACH_WIN_100_GAMES");
}