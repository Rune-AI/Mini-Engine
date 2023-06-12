#include "PumpCommand.h"
#include "Player.h"
#include <Entity.h>


void PumpCommand::Execute()
{
	m_Entity->GetComponent<DigDug::Player>()->OnPumpShoot();
}
