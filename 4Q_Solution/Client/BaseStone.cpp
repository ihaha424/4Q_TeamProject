#include "pch.h"
#include "BaseStone.h"

BaseStone::BaseStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)\
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void BaseStone::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	StaticObject::Prepare(componentFactory);
	_trigger = componentFactory->Clone<TriggerBox>(this);
}

void BaseStone::DisposeComponents()
{
	StaticObject::DisposeComponents();
	_trigger->Dispose();
}

void BaseStone::PreInitialize(const Engine::Modules& modules)
{
	StaticObject::PreInitialize(modules);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	PhysicsManager->CreateStaticBoundBoxActor(&_trigger->_triggerBox, _boxScale, _transform);
	_rigidStatc->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_trigger->_triggerBox);
}

