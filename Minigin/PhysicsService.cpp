#include "PhysicsService.h"
#include "RigidBody2DComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

BearBones::PhysicsService::PhysicsService()
{
	m_PhysicsThread = std::jthread(&PhysicsService::PhysicsLoop, this);
}

BearBones::PhysicsService::~PhysicsService()
{
	HaltPhysics();
}

void BearBones::PhysicsService::AddRigidBody(RigidBody2DComponent* rb)
{
	std::unique_lock<std::mutex> lock(m_PhysicsMutex);

	m_NewBodies.push_back(rb);
	
	m_PhysicsCondition.notify_one();
}

void BearBones::PhysicsService::CleanAll()
{
	std::unique_lock<std::mutex> lock(m_PhysicsMutex);

	for (auto& rb : m_RigidBodies)
	{
		rb->GetOwner()->MarkForDeletion();
	}

	m_Collisions.clear();
	m_NewBodies.clear();
}

void BearBones::PhysicsService::Update()
{
	m_BodiesToErase.clear();

    for (size_t mainRigidBodyID{}; mainRigidBodyID < m_RigidBodies.size(); ++mainRigidBodyID)
    {
        RigidBody2DComponent* rb = m_RigidBodies[mainRigidBodyID];

        if (rb->GetOwner()->IsMarkedForDeletion() && !m_BodiesToErase.contains(rb))
        {
            m_BodiesToErase.insert(rb);
            continue;
        }

        for (size_t otherRigidBodyID{}; otherRigidBodyID < m_RigidBodies.size(); ++otherRigidBodyID)
        {
            RigidBody2DComponent* other = m_RigidBodies[otherRigidBodyID];

            if (other->GetOwner()->IsMarkedForDeletion() && !m_BodiesToErase.contains(other))
            {
                m_BodiesToErase.insert(other);
                continue;
            }

            //if (mainRigidBodyID >= m_RigidBodies.size() || otherRigidBodyID >= m_RigidBodies.size())
            //    continue;


            if (rb == other)
                continue;

            if (rb == nullptr || other == nullptr)
                continue;

            if (rb->GetOwner() == nullptr || other->GetOwner() == nullptr)
                continue;

            if (rb->GetOwner() == other->GetOwner())
                continue;

            if (rb->GetOwner()->IsMarkedForDeletion() || other->GetOwner()->IsMarkedForDeletion())
                continue;

            auto selfCollider = rb->GetCollider();
            auto otherCollider = other->GetCollider();

            auto selfPosition = rb->GetOwner()->GetTransform()->GetWorldPosition();;
            auto otherPosition = other->GetOwner()->GetTransform()->GetWorldPosition();;

            bool isColliding =
                (
                    selfPosition.x - (selfCollider.width / 2) + (selfCollider.width / 2) < otherPosition.x + (otherCollider.width / 2) + (otherCollider.width / 2) &&
                    selfPosition.x + (selfCollider.width / 2) + (selfCollider.width / 2) > otherPosition.x - (otherCollider.width / 2) + (otherCollider.width / 2) &&
                    selfPosition.y - (selfCollider.height / 2) + (selfCollider.width / 2) < otherPosition.y + (otherCollider.height / 2) + (otherCollider.width / 2) &&
                    selfPosition.y + (selfCollider.height / 2) + (selfCollider.width / 2) > otherPosition.y - (otherCollider.height / 2) + (otherCollider.width / 2)
                    );

            const bool collisionExists = (m_Collisions.contains(rb));
            const bool collisionExistsForOther = m_Collisions[rb].contains(other);


            if (isColliding && collisionExists && collisionExistsForOther)
            {
                rb->OnCollision(other);
                continue;
            }

            if (isColliding && collisionExists && !collisionExistsForOther)
            {
                rb->OnCollisionEnter(other);
                m_Collisions[rb].insert(other);
                continue;
            }

            if (!isColliding && collisionExists && collisionExistsForOther)
            {
                rb->OnCollisionExit(other);
                m_Collisions[rb].erase(other);
                continue;
            }
        }
    }
}

void BearBones::PhysicsService::PhysicsLoop()
{
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(m_PhysicsMutex);
            m_PhysicsCondition.wait(lock, [this]() { return m_stopRequested || !m_RigidBodies.empty() || !m_NewBodies.empty(); });

            // Add new bodies
            for (auto& rb : m_NewBodies)
            {
                m_RigidBodies.push_back(rb);
                if (!m_Collisions.contains(rb))
                {
                    m_Collisions[rb] = std::set<RigidBody2DComponent*>();
                }
            }
            m_NewBodies.clear();

            // Remove bodies
            for (auto& rb : m_BodiesToErase)
            {
                m_RigidBodies.erase(std::remove(m_RigidBodies.begin(), m_RigidBodies.end(), rb), m_RigidBodies.end());

                // Delete from m_Collisions
                m_Collisions.erase(rb);

                // Delete from other m_Collisions
                for (auto& [id, collisions] : m_Collisions)
                {
                    collisions.erase(rb);
                }

                // Make gameobject as can be destroyed (needs to be done on main thread)
                rb->GetOwner()->SetCanBeDestroyed(true);
            }
            m_BodiesToErase.clear();

            // Stop if requested
            if (m_stopRequested)
                break;
        }

        Update();
    }
}

void BearBones::PhysicsService::HaltPhysics()
{
    m_stopRequested = true;
    m_PhysicsCondition.notify_one();
    m_PhysicsThread.join();
}
