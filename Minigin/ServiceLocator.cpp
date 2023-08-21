#include "ServiceLocator.h"
#include "ISoundService.h"
#include <thread>

BearBones::ISoundService* BearBones::ServiceLocator::m_soundService{ &m_defaultSoundService };

void BearBones::ServiceLocator::RegisterSoundService(ISoundService* soundService)
{
    m_soundService = (soundService == nullptr)
        ? &m_defaultSoundService
        : soundService;
}

BearBones::ISoundService* BearBones::ServiceLocator::GetSoundService()
{
    return m_soundService;
}

void BearBones::ServiceLocator::DestroyServices()
{
    if (m_soundService != &m_defaultSoundService)
    {
        delete m_soundService;
        m_soundService = &m_defaultSoundService;
    }
}