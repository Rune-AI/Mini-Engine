#include "ServiceLocator.h"
#include "ISoundService.h"
#include "IPhysicsService.h"

ISoundService* ServiceLocator::m_soundService{ &m_defaultSoundService };

void ServiceLocator::RegisterSoundService(ISoundService* soundService)
{
    m_soundService = (soundService == nullptr)
        ? &m_defaultSoundService
        : soundService;
}

void ServiceLocator::RegisterPhysicsService(IPhysicsService* physicsService)
{
    m_physicsService = (physicsService == nullptr)
        ? &m_defaultPhysicsService
        : physicsService;
}

ISoundService* ServiceLocator::GetSoundService()
{
    return m_soundService;
}

IPhysicsService* ServiceLocator::GetPhysicsService()
{
    return m_physicsService;
}

void ServiceLocator::DestroyServices()
{
    if (m_soundService != &m_defaultSoundService)
    {
        delete m_soundService;
        m_soundService = &m_defaultSoundService;
    }
}