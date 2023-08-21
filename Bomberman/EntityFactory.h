#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include <Entity.h>

namespace Bomberman
{
	class EntityFactory final
	{
	public:
		EntityFactory();
		virtual ~EntityFactory() = default;

		EntityFactory(const EntityFactory& other) = delete;
		EntityFactory(EntityFactory&& other) = delete;
		EntityFactory& operator=(const EntityFactory& other) = delete;
		EntityFactory& operator=(EntityFactory&& other) = delete;


		std::unique_ptr<BearBones::Entity> CreateBalloom(BearBones::Entity* Level);
		std::unique_ptr<BearBones::Entity> CreateOneal(BearBones::Entity* Level);
		std::unique_ptr<BearBones::Entity> CreateDoll(BearBones::Entity* Level);
		std::unique_ptr<BearBones::Entity> CreateMinvo(BearBones::Entity* Level);
		std::unique_ptr<BearBones::Entity> CreatePlayer(BearBones::Entity* Level);
		std::unique_ptr<BearBones::Entity> CreateDoor(BearBones::Entity* Level);
		std::unique_ptr<BearBones::Entity> CreateFlamePowerup();
		std::unique_ptr<BearBones::Entity> CreateExtraBombPowerup();
		std::unique_ptr<BearBones::Entity> CreateBalloomVisual(BearBones::Entity* Level);

	private:
		std::unique_ptr<BearBones::Entity> CreateEnemyBase(BearBones::Entity* Level);
	};
}

#endif