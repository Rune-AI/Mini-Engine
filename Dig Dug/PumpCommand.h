#ifndef PUMP_COMMAND_H
#define PUMP_COMMAND_H

#include <Command.h>
class PumpCommand final : public Command
{
public:
	PumpCommand(Entity* obj) : Command{ obj } {};
	virtual void Execute() override;
};

#endif