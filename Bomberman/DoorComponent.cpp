#include "DoorComponent.h"
#include "Entity.h"
#include "PlayerController.h"
#include <iostream>
#include "GameManager.h"
#include "LevelComponent.h"


Bomberman::DoorComponent::DoorComponent(BearBones::Entity* object, BearBones::Entity *Level)
	: TriggerComponent{ object }
	, m_pLevel{ Level->GetComponent<LevelComponent>()}
{

}
void Bomberman::DoorComponent::Update()
{
	TriggerComponent::Update();
}
void Bomberman::DoorComponent::Render() const
{
}
void Bomberman::DoorComponent::OnTouch(BearBones::Entity* other)
{
	if (other->HasComponent<Bomberman::PlayerController>())
	{
		//Check if all enemies are dead
		/*std::vector<BearBones::Entity*> enemies{};
		m_pLevel->GetEnemies(enemies);
		if (enemies.size() > 0)
		{
			for (auto enemy : enemies)
			{
				if (enemy->IsActive())
				{
					return;
				}
			}
		}*/

		//Win game, next level/restart
		std::cout << "You win!" << std::endl;
		Bomberman::GameManager::GetInstance().ResetGame();
	}
}


