#include "pch.h"
#include "TriggerBox.h"

TriggerBox::TriggerBox()
	: _triggerBox{ nullptr }
{
}

TriggerBox::~TriggerBox()
{
}

void TriggerBox::BindBeginInteraction(const InteractionFunction& callback)
{
	_begineFunction = callback;
}

void TriggerBox::BindEndInteraction(const InteractionFunction& callback)
{
	_endFunction = callback;
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
	_triggerBox->BindCollision([this](Engine::Physics::TriggerEvent event)
			{
				if(_begineFunction)
					_begineFunction();
			}
		, Engine::Physics::TriggerType::OnOverlapBegin);
	_triggerBox->BindCollision([this](Engine::Physics::TriggerEvent event)
			{
				if (_endFunction)
					_endFunction();
			}
		, Engine::Physics::TriggerType::OnOverlapEnd);

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
