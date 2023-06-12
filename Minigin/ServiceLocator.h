#pragma once
#include "IPhysicsService.h"
#include "ISoundService.h"

class ServiceLocator final
{
public:
    ServiceLocator(const ServiceLocator& other) = delete;
    ServiceLocator(ServiceLocator&& other) = delete;
    ServiceLocator& operator=(const ServiceLocator& other) = delete;
    ServiceLocator& operator=(ServiceLocator&& other) = delete;

    static void RegisterSoundService(ISoundService* soundService);
    static void RegisterPhysicsService(IPhysicsService* physicsService);
    static ISoundService* GetSoundService();
    static IPhysicsService* GetPhysicsService();

    static void DestroyServices();

private:
    ServiceLocator() = default;
    ~ServiceLocator() = default;

    inline static NullSoundService m_defaultSoundService{};
    static ISoundService* m_soundService;

    inline static NullPhysicsService m_defaultPhysicsService{};
    static IPhysicsService* m_physicsService;
};
