
#include "Command.h"

class DieCommand final : public Command
{
public:
	DieCommand(Entity* gobj) : Command{ gobj } {};
	virtual void Execute() override;
};

