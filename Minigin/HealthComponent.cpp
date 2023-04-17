#include "HealthComponent.h"
#include <numeric>

HealthComponent::HealthComponent(Entity* entity)
	:Component{ entity }
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update()
{
}

void HealthComponent::Render() const
{
}

void HealthComponent::SetHealth(int health)
{
	m_Health = health;
}

int HealthComponent::GetHealth() const
{
	return m_Health;
}

void HealthComponent::TakeDamage(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		m_Health = 0;
	}
	m_Health = std::abs(m_Health);
	

	NotifyObservers(m_Health);
}