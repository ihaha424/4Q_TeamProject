#include "pch.h"
#include "TriggerArea.h"

TriggerArea::TriggerArea(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)\
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void TriggerArea::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	StaticObject::Prepare(componentFactory);
	_trigger = componentFactory->Clone<TriggerBox>(this);
}

void TriggerArea::DisposeComponents()
{
	StaticObject::DisposeComponents();
	_trigger->Dispose();
}

void TriggerArea::PreInitialize(const Engine::Modules& modules)
{
	StaticObject::PreInitialize(modules);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	PhysicsManager->CreateStaticBoundBoxActor(&_trigger->_triggerBox, _boxScale, _transform);
	_rigidStatc->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_trigger->_triggerBox);


	// TODO Bind Trigger(상속받은 오브젝트가 PreInitialize단계에서 트리거를 바인딩 하면 됨)
}

