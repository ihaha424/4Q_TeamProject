#pragma once
class PhysicsChractorController
{
};

#include <functional>
#include <iostream>

template<typename T>
class PhysicsComponent
{
public:
    PhysicsComponent() : _owner(nullptr) {}

    using Function = std::function<void(T* other)>;

    void BindFunction(const Function& onCollision)
    {
        _onCollision = onCollision;
    }

    void SetOwner(T* owner)
    {
        _owner = owner;
    }

    void Execute()
    {
        _onCollision(_owner);
    }

    Function _onCollision;

    T* _owner;
};

class EngineObject;

class EngineComponent
{
public:
    EngineComponent() : _owner(nullptr), _physicsComponent(nullptr)
    {
        _physicsComponent = new PhysicsComponent<EngineComponent>();
        _physicsComponent->SetOwner(this);
    }

    ~EngineComponent()
    {
        delete _physicsComponent;
    }

    EngineObject* GetOwner() const
    {
        return _owner;
    }

    void SetOwner(EngineObject* owner)
    {
        _owner = owner;
    }

    void BindFunction(const PhysicsComponent<EngineComponent>::Function& onCollision) const
    {
        _physicsComponent->BindFunction(onCollision);
    }

    EngineObject* _owner;
    PhysicsComponent<EngineComponent>* _physicsComponent;
};

class EngineObject
{
public:
    EngineObject() : _engineComponent(nullptr), _a(10)
    {
        _engineComponent = new EngineComponent();
        _engineComponent->SetOwner(this);
        _engineComponent->BindFunction([this](EngineComponent* other)
            {
                std::cout << other->GetOwner()->_a << std::endl;
            });
    }

    ~EngineObject()
    {
        delete _engineComponent;
    }

    EngineComponent* _engineComponent;
    int _a;
};

class ServerObject
{
public:
    ServerObject() : _physicsComponent(nullptr), _b(20)
    {
        _physicsComponent = new PhysicsComponent<ServerObject>();
        _physicsComponent->SetOwner(this);
        _physicsComponent->BindFunction([this](const ServerObject* other)
            {
                std::cout << other->_b << std::endl;
            });
    }

    ~ServerObject()
    {
        delete _physicsComponent;
    }

    PhysicsComponent<ServerObject>* _physicsComponent;
    int _b;
};


int main()
{
    EngineObject engineObject;
    ServerObject serverObject;
    engineObject._engineComponent->_physicsComponent->Execute();
    serverObject._physicsComponent->Execute();
    return 0;
};