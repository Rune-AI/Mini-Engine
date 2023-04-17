#include "DieCommand.h"
#include "Entity.h"
#include "HealthComponent.h"

void DieCommand::Execute()
{
	auto healthComponent = m_Entity->GetComponent<HealthComponent>();
	healthComponent->TakeDamage(1);
}