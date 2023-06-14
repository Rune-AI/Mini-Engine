#include "ServiceLocator.h"
#include "ISoundService.h"

BearBones::ISoundService* BearBones::ServiceLocator::m_soundService{ &m_defaultSoundService };
IPhysicsService* BearBones::ServiceLocator::m_physicsService{&m_defaultPhysicsService};

void BearBones::ServiceLocator::RegisterSoundService(ISoundService* soundService)
{
    m_soundService = (soundService == nullptr)
        ? &m_defaultSoundService
        : soundService;
}

void BearBones::ServiceLocator::RegisterPhysicsService(IPhysicsService* physicsService)
{
    m_physicsService = (physicsService == nullptr)
        ? &m_defaultPhysicsService
        : physicsService;
}

BearBones::ISoundService* BearBones::ServiceLocator::GetSoundService()
{
    return m_soundService;
}

IPhysicsService* BearBones::ServiceLocator::GetPhysicsService()
{
    return m_physicsService;
}

void BearBones::ServiceLocator::DestroyServices()
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