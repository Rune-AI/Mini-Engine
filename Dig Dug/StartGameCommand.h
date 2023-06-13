#ifndef START_COMMAND_H
#define START_COMMAND_H

#include <Command.h>
class StartGameCommand final : public Command
{
public:
	StartGameCommand(Entity* obj) : Command{ obj } {};
	virtual void Execute() override;
};

#endif