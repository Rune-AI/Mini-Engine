#include "ServiceLocator.h"
#include "ISoundService.h"

ISoundService* ServiceLocator::m_soundService{ &m_defaultSoundService };

void ServiceLocator::RegisterSoundService(ISoundService* soundService)
{
    m_soundService = (soundService == nullptr)
        ? &m_defaultSoundService
        : soundService;
}

ISoundService* ServiceLocator::GetSoundService()
{
    return m_soundService;
}

void ServiceLocator::DestroyServices()
{
    if (m_soundService != &m_defaultSoundService)
    {
        delete m_soundService;
        m_soundService = &m_defaultSoundService;
    }
}