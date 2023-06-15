#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATOR_H

#include "ISoundService.h"

namespace BearBones
{
    class ServiceLocator final
    {
    public:
        ServiceLocator(const ServiceLocator& other) = delete;
        ServiceLocator(ServiceLocator&& other) = delete;
        ServiceLocator& operator=(const ServiceLocator& other) = delete;
        ServiceLocator& operator=(ServiceLocator&& other) = delete;

        static void RegisterSoundService(ISoundService* soundService);
        static ISoundService* GetSoundService();

        static void DestroyServices();

    private:
        ServiceLocator() = default;
        ~ServiceLocator() = default;

        inline static NullSoundService m_defaultSoundService{};
        static ISoundService* m_soundService;
    };
}

#endif //SERVICE_LOCATOR_H