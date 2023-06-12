#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <Command.h>
#include <glm/ext/vector_float2.hpp>
class MoveCommand final : public Command
{
public:
	MoveCommand(Entity* obj) : Command{ obj } {};
	virtual void Execute() override;

private:
	float m_speed{ 250 };
};

#endif