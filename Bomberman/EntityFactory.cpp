#include "EntityFactory.h"
#include "Entity.h"
#include "EnemyAIController.h"
#include "AnimationComponent.h"
#include "PlayerController.h"
#include "PointsOnDeathComponent.h"
#include "LevelComponent.h"
#include "DoorComponent.h"
#include "FlamePowerpupComponent.h"
#include "KillVolumeComponent.h"
#include "KillPlayerVolumeComponent.h"
#include "ExtraBombComponent.h"

Bomberman::EntityFactory::EntityFactory()
{
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateBalloom(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> enemy = CreateEnemyBase(Level);

	AnimationData Right{ 210, 213};
	AnimationData Left{ 214, 217 };
	AnimationData Death{ 218, 221 };
	auto animcomp = enemy->GetComponent<Bomberman::AnimationComponent>();
	animcomp->SetRightAnimation(Right);
	animcomp->SetUpAnimation(Right);
	animcomp->SetLeftAnimation(Left);
	animcomp->SetDownAnimation(Left);
	animcomp->SetDeathAnimation(Death);

	auto controller = enemy->GetComponent<Bomberman::EnemyAIController>();
	controller->SetSpeed(24.f);

	return enemy;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateOneal(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> enemy = CreateEnemyBase(Level);

	AnimationData Right{ 224, 227 };
	AnimationData Left{ 228, 231 };
	AnimationData Death{ 232, 235 };
	auto animcomp = enemy->GetComponent<Bomberman::AnimationComponent>();
	animcomp->SetRightAnimation(Right);
	animcomp->SetUpAnimation(Right);
	animcomp->SetLeftAnimation(Left);
	animcomp->SetDownAnimation(Left);
	animcomp->SetDeathAnimation(Death);

	auto controller = enemy->GetComponent<Bomberman::EnemyAIController>();
	controller->SetSpeed(36.f);
	controller->SetIntelligence(Intelligence::Smart);

	return enemy;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateDoll(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> enemy = CreateEnemyBase(Level);

	AnimationData Right{ 224+14, 227+14 };
	AnimationData Left{ 228+14, 231+14 };
	AnimationData Death{ 232+14, 235+14 };
	auto animcomp = enemy->GetComponent<Bomberman::AnimationComponent>();
	animcomp->SetRightAnimation(Right);
	animcomp->SetUpAnimation(Right);
	animcomp->SetLeftAnimation(Left);
	animcomp->SetDownAnimation(Left);
	animcomp->SetDeathAnimation(Death);

	auto controller = enemy->GetComponent<Bomberman::EnemyAIController>();
	controller->SetSpeed(36.f);
	controller->SetIntelligence(Intelligence::Dumb);

	return enemy;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateMinvo(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> enemy = CreateEnemyBase(Level);
	AnimationData Right{ 224 + 28, 227 + 28 };
	AnimationData Left{ 228 + 28, 231 + 28 };
	AnimationData Death{ 232 + 28, 235 + 28 };
	auto animcomp = enemy->GetComponent<Bomberman::AnimationComponent>();
	animcomp->SetRightAnimation(Right);
	animcomp->SetUpAnimation(Right);
	animcomp->SetLeftAnimation(Left);
	animcomp->SetDownAnimation(Left);
	animcomp->SetDeathAnimation(Death);

	auto controller = enemy->GetComponent<Bomberman::EnemyAIController>();
	controller->SetSpeed(48.f);
	controller->SetIntelligence(Intelligence::Smart);
	return enemy;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreatePlayer(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> player = std::make_unique<BearBones::Entity>();
	player->AddComponent<Bomberman::PlayerController>(Level);
	auto controller = player->GetComponent<Bomberman::PlayerController>();
	player->AddComponent<Bomberman::AnimationComponent>("Resources/Sprites/GeneralSprites.png", controller);
	player->SetZOrder(99);

	AnimationData Right{ 14, 17 };
	AnimationData Left{ 0, 3 };
	AnimationData Up{ 18, 21 };
	AnimationData Down{ 4, 7 };
	AnimationData Death{ 28, 35 };
	auto animcomp = player->GetComponent<Bomberman::AnimationComponent>();
	animcomp->SetRightAnimation(Right);
	animcomp->SetUpAnimation(Up);
	animcomp->SetLeftAnimation(Left);
	animcomp->SetDownAnimation(Down);
	animcomp->SetDeathAnimation(Death);

	animcomp->SetSpriteTimePerFrame(0.1f);

	controller->SetSpeed(48.f);

	return player;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateDoor(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> door = std::make_unique<BearBones::Entity>();
	door->AddComponent<Bomberman::DoorComponent>(Level);
	door->AddComponent<BearBones::SpriteComponent>("Resources/Sprites/GeneralSprites.png");
	door->SetZOrder(0);


	auto sprite = door->GetComponent<BearBones::SpriteComponent>();
	sprite->SetSpriteIndexStart(53);
	sprite->SetSpriteIndexEnd(54);
	sprite->SetIsLooping(false);
	sprite->SetIsPlaying(false);
	return door;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateFlamePowerup()
{
	auto powerup = std::make_unique<BearBones::Entity>();
	powerup->AddComponent<FlamePowerpupComponent>();
	
	powerup->SetZOrder(0);
	return powerup;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateExtraBombPowerup()
{
	auto powerup = std::make_unique<BearBones::Entity>();
	powerup->AddComponent<ExtraBombComponent>();

	powerup->SetZOrder(0);
	return powerup;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateBalloomVisual(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> enemy = CreateEnemyBase(Level);

	AnimationData Right{ 210, 213 };
	AnimationData Left{ 214, 217 };
	AnimationData Death{ 218, 221 };
	auto animcomp = enemy->GetComponent<Bomberman::AnimationComponent>();
	animcomp->SetRightAnimation(Right);
	animcomp->SetUpAnimation(Right);
	animcomp->SetLeftAnimation(Left);
	animcomp->SetDownAnimation(Left);
	animcomp->SetDeathAnimation(Death);
	animcomp->SetSpriteTimePerFrame(0.1f);
	return enemy;
}

std::unique_ptr<BearBones::Entity> Bomberman::EntityFactory::CreateEnemyBase(BearBones::Entity* Level)
{
	std::unique_ptr<BearBones::Entity> enemy = std::make_unique<BearBones::Entity>();
	enemy->AddComponent<Bomberman::EnemyAIController>(Level);
	auto controller = enemy->GetComponent<Bomberman::EnemyAIController>();
	enemy->AddComponent<Bomberman::AnimationComponent>("Resources/Sprites/GeneralSprites.png", controller);

	auto levelcomp = Level->GetComponent<Bomberman::LevelComponent>();
	enemy->AddComponent<Bomberman::PointsOnDeathComponent>(levelcomp);
	auto destruct = enemy->GetComponent<Bomberman::PointsOnDeathComponent>();
	levelcomp->AddDestructible(destruct);

	enemy->AddComponent<Bomberman::KillPlayerVolumeComponent>(Level);

	enemy->SetZOrder(1);
	return enemy;
}
