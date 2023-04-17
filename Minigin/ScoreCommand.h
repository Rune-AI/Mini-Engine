#include "Command.h"

class ScoreCommand final : public Command
{
public:
	ScoreCommand(Entity* gobj) : Command{ gobj } {};
	virtual void Execute() override;
};
