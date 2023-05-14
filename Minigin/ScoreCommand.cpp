#include "ScoreCommand.h"
#include "Entity.h"
#include "ScoreComponent.h"

void ScoreCommand::Execute()
{
	auto scoreComponent = m_Entity->GetComponent<ScoreComponent>();
	scoreComponent->AddScore(1);
}