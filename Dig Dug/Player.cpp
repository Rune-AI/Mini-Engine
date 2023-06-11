#include "Player.h"

#include <TextureComponent.h>
#include <ResourceManager.h>

DigDug::Player::Player(Entity* object)
    : Component(object)
    , m_PumpTexture{ ResourceManager::GetInstance().LoadTexture("")}
    , m_IsPumping{ false }
{

    
}

void DigDug::Player::Update()
{
}

void DigDug::Player::Pump()
{
    if (m_IsPumping) return;

    m_IsPumping = true;


    /*auto HeadHitbox = std::make_unique<Entity>();
    auto HeadVisual= std::make_unique<Entity>();

    Head->AddComponent<TextureComponent>(m_PumpTexture);
    Head->

    projectile->AddComponent<Galaga::Projectile>(glm::vec2{ 0.f, 1.f }, glm::vec2{ 0.f, -200.f });
    projectile->AddComponent<Galaga::AutoKill>(15.f);
    projectile->AddComponent<Engine::RigidBody2D>(Engine::RigidBody2DCollider{5, 5});
    projectile->AddTag("bullet");

    Engine::SceneManager::GetInstance().GetActiveScene()->Instantiate(projectile);
    L_DEBUG("Adding bullet");

    auto ss = Engine::ServiceLocator::GetSoundService();
    ss->Play("Resources/Audio/shoot_short.wav");

    m_ShootCooldownTimer = 0.f;*/
}

void DigDug::Player::OnPumpHit()
{
}
