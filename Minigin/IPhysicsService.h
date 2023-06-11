#ifndef PHYSICS_SERVICE_INTERFACE_H
#define PHYSICS_SERVICE_INTERFACE_H

class RigidBody2DComponent;

class IPhysicsService
{
public:
    virtual ~IPhysicsService() = default;

    virtual void AddRigidBody(RigidBody2DComponent* rb) = 0;
    virtual void Update() = 0;
    virtual void CleanAll() = 0;

};

class NullPhysicsService final : public IPhysicsService
{
public:
    NullPhysicsService() = default;
    ~NullPhysicsService() = default;

    virtual void AddRigidBody(RigidBody2DComponent*) {};
    virtual void Update() {};
    virtual void CleanAll() {};
};

#endif