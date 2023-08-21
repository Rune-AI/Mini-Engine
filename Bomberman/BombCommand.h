#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H
#include <Command.h>
#include <Entity.h>

namespace Bomberman
{
	class LevelComponent;
	class BombCommand : public BearBones::Command
	{
	public:
		BombCommand(BearBones::Entity* player, LevelComponent* level);
		virtual void Execute() override;

	private:
		LevelComponent* m_pLevel;
	};
}
#endif
