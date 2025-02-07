#include "pch.h"
#include "TriggerBox.h"

TriggerBox::TriggerBox()
	: _triggerBox{ nullptr }
{
}

TriggerBox::~TriggerBox()
{
}

void TriggerBox::Interaction()
{
	_function();
}

void TriggerBox::BindInteraction(const InteractionFunction& callback)
{
	_function = callback;
}

void TriggerBox::Initialize(const Engine::Modules& modules)
{
	Component::Initialize(modules);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	static_cast<Engine::Physics::RigidStaticComponent*>(_triggerBox)->Initialize();
	_triggerBox->SetOwner(GetOwner());
	_triggerBox->SetFlag(Engine::Physics::CollisionType::Collision, false);
	_triggerBox->SetFlag(Engine::Physics::CollisionType::Trigger, true);
	_triggerBox->SetFlag(Engine::Physics::CollisionType::Scene_Query, false);
}
void TriggerBox::Update(float deltaTime)
{
	Component::Update(deltaTime);
}

void TriggerBox::FixedUpdate()
{
	Component::FixedUpdate();
	static_cast<Engine::Physics::RigidStaticComponent*>(_triggerBox)->FixedUpdate();
}

void TriggerBox::Finalize()
{
	Component::Finalize();
	static_cast<Engine::Physics::RigidStaticComponent*>(_triggerBox)->Finalize();
}
