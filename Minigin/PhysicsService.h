#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H

#include "IPhysicsService.h"
#include "RigidBody2DComponent.h"

#include <vector>
#include <unordered_set>
#include <mutex>
#include <unordered_map>
#include <set>

namespace BearBones
{
    class RigidBody2D;

    class PhysicsService final : public IPhysicsService
    {
    public:
        PhysicsService();
        ~PhysicsService();
        void AddRigidBody(RigidBody2DComponent* rb);
        void CleanAll();

        void Update();

    private:
        void PhysicsLoop();
        void HaltPhysics();

        std::vector<RigidBody2DComponent*> m_RigidBodies;
        std::vector<RigidBody2DComponent*> m_NewBodies{};
        std::unordered_set<RigidBody2DComponent*> m_BodiesToErase{};

        std::mutex m_PhysicsMutex{};
        std::mutex m_AddNewBodiesMutex{};
        std::condition_variable m_PhysicsCondition{};
        std::condition_variable m_AddNewBodiesCondition{};
        std::atomic<bool> m_stopRequested{ false };
        std::jthread m_PhysicsThread;


        // rb id to list of colliding rb ids
        std::unordered_map<RigidBody2DComponent*, std::set<RigidBody2DComponent*>> m_Collisions{};
    };
}

#endif