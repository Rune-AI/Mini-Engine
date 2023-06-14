#ifndef COMMAND_H
#define COMMAND_H

namespace BearBones
{
	class Command
	{
	public:
		Command(class Entity* gobj) : m_Entity{ gobj } {};
		virtual ~Command() {};
		virtual void Execute() = 0;
		virtual void Undo() {};

	protected:
		Entity* m_Entity{};
	};
}

#endif //COMMAND_H