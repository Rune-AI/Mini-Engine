#include "Player.h"

#include <TextureComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include <Renderer.h>
#include <Entity.h>
#include <TransformComponent.h>
#include <EngineTime.h>

DigDug::Player::Player(Entity* object)
    : Component(object)
    , m_pumpTexture{ ResourceManager::GetInstance().LoadTexture("Resources/Sprites/Pump/head.png")}
    , m_ropeTexture{ ResourceManager::GetInstance().LoadTexture("Resources/Sprites/Pump/rope.png")}
    , m_idleTexture{ ResourceManager::GetInstance().LoadTexture("Resources/Sprites/Character/Walk/0.png") }
    , m_IsPumping{ false }
    , m_pumpHeadDistance{}
    , m_pumpHeadSpeed{ 100.f }
    
    , m_pumpPulseTime{}
    , m_pumpPulseInterval{1.f}
{
    m_pumpHeadMaxDistance = m_ropeTexture->GetSize().x * 3.f;
    
}

void DigDug::Player::Update()
{
    //m_moveDirection = glm::vec2{ 0,0 };
    HandleControllerInput();
    HandleKeyboardInput();
    //m_moveDirection.y = -m_moveDirection.y;


    Move();


    if (m_moveDirection.x + m_moveDirection.y != 0.f)
    {
        m_angle = atan2f(m_moveDirection.y, m_moveDirection.x) * 180.f / float(M_PI);
    }

    UpdatePump();
}

void DigDug::Player::Render() const
{
    const auto pos = m_pOwner->GetTransform()->GetWorldPosition();
    glm::vec2 textureSize = m_idleTexture->GetSize();
    auto scale = m_pOwner->GetTransform()->GetWorldScale();
    textureSize *= scale;

    
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (m_angle > 90.f)
    {
		//angle -= 90.f;
		flip = SDL_FLIP_VERTICAL;
	}
    else if (m_angle < -90.f)
    {
        flip = SDL_FLIP_VERTICAL;
    }


    Renderer::GetInstance().RenderTextureEx(*m_idleTexture,
        pos.x, pos.y,
        float(textureSize.x), float(textureSize.y),
        m_angle, flip);


    if (m_IsPumping)
    {
        RenderPump();
    }
}

void DigDug::Player::Move()
{

    if (!m_IsMovementButtonPressed) return;
    m_IsMovementButtonPressed = false;
    if (m_moveDirection == glm::vec2{ 0,0 }) return;

    auto pos = m_pOwner->GetTransform()->GetLocalPosition();
    m_pOwner->GetTransform()->SetLocalPosition(pos + m_moveDirection * 100.f * TIME.GetDeltaTime());
}

void DigDug::Player::HandleControllerInput()
{
    auto direction = InputManager::GetInstance().GetController()->GetLeftThumbStick();
    if (glm::length(direction) > 0.1f)
    {
		m_moveDirection = direction;
        m_IsMovementButtonPressed = true;
		return;
	}
}

void DigDug::Player::HandleKeyboardInput()
{
    auto keyboard = InputManager::GetInstance().GetKeyboard();
    
    if (keyboard->IsPressed(SDL_SCANCODE_W))
    {
        m_moveDirection.x = 0.f;
        m_moveDirection.y = -1.f;
        m_IsMovementButtonPressed = true;
    }
    else if (keyboard->IsPressed(SDL_SCANCODE_S))
    {
        m_moveDirection.x = 0.f;
		m_moveDirection.y = 1.f;
        m_IsMovementButtonPressed = true;
	}
    else if (keyboard->IsPressed(SDL_SCANCODE_A))
    {
		m_moveDirection.x = -1.f;
        m_moveDirection.y = 0.f;
        m_IsMovementButtonPressed = true;
	}
    else if (keyboard->IsPressed(SDL_SCANCODE_D))
    {
		m_moveDirection.x = 1.f;
        m_moveDirection.y = 0.f;
        m_IsMovementButtonPressed = true;
	}
}

void DigDug::Player::UpdatePump()
{
    if (m_IsPumping)
    {
        m_pumpHeadDistance = m_pumpHeadDistance + m_pumpHeadSpeed * TIME.GetDeltaTime();
        if (m_pumpHeadDistance > m_pumpHeadMaxDistance)
        {
            //reset
            m_IsPumping = false;
            m_pumpHeadDistance = 0.f;
            m_pumpPulseTime = 0.f;
		}
	}
}

void DigDug::Player::RenderPump() const
{

    auto pos = m_pOwner->GetTransform()->GetWorldPosition();
    pos += m_moveDirection * m_pumpHeadDistance;


    glm::vec2 textureSize = m_pumpTexture->GetSize();
    auto scale = m_pOwner->GetTransform()->GetWorldScale();
    textureSize *= scale;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (m_angle > 90.f)
    {
        flip = SDL_FLIP_VERTICAL;
    }
    else if (m_angle < -90.f)
    {
        flip = SDL_FLIP_VERTICAL;
    }

    Renderer::GetInstance().RenderTextureEx(*m_pumpTexture,
        pos.x, pos.y,
        float(textureSize.x), float(textureSize.y),
        m_angle, flip);

    for (size_t i = 0; i < m_pumpHeadDistance/textureSize.x - 1 ; i++)
    {
        pos -= m_moveDirection * textureSize.x;
		Renderer::GetInstance().RenderTextureEx(*m_ropeTexture,
            pos.x, pos.y,
            float(textureSize.x), float(textureSize.y),
            m_angle, flip);
    }
}

void DigDug::Player::OnPumpShoot()
{
    m_IsPumping = true;
}

void DigDug::Player::OnPumpHit()
{
}
