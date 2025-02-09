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
	
	Engine::Physics::RigidComponentDesc desc;
	desc.rigidType = Engine::Physics::RigidBodyType::Static;
	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
	desc.shapeDesc.geometryDesc.data = { _boxScale.x, _boxScale.y, _boxScale.z, 0 };
	desc.shapeDesc.isExclusive = true;
	desc.shapeDesc.materialDesc.data = { 0.f,0.f,0.f };

	Engine::Transform shapeTransform{};
	PhysicsManager->CreateStatic(&_trigger->_triggerBox, desc, _transform, shapeTransform);
	_trigger->_triggerBox->SetOwner(this);

	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_trigger->_triggerBox);


	// TODO Bind Trigger(상속받은 오브젝트가 PreInitialize단계에서 트리거를 바인딩 하면 됨)
	// TestCode TODO: Delete
	_trigger->BindBeginInteraction([]() {
			std::cout << "TriggerBegine!\n";
		});
	_trigger->BindEndInteraction([]() {
		std::cout << "TriggerEnd!\n";
		});
}

