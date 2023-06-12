#include "ServiceLocator.h"
#include "ISoundService.h"

ISoundService* ServiceLocator::m_soundService{ &m_defaultSoundService };
IPhysicsService* ServiceLocator::m_physicsService{&m_defaultPhysicsService};

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
    if (m_physicsService != &m_defaultPhysicsService)
    {
        delete m_physicsService;
        m_physicsService = &m_defaultPhysicsService;
    }
}