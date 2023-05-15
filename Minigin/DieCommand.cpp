#include "DieCommand.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "ServiceLocator.h"

void DieCommand::Execute()
{
	auto healthComponent = m_Entity->GetComponent<HealthComponent>();
	healthComponent->TakeDamage(1);

	auto ss = ServiceLocator::GetSoundService();
	ss->Play("Resources/Audio/sonic-youre-too-slow.wav", 0.5f);
}