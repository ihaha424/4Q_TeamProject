#include "pch.h"
#include "BaseStone.h"

BaseStone::BaseStone(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: InteractObject(meshPath, physicsPath)
{
}

void BaseStone::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_sound = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
	_trigger = componentFactory->Clone<TriggerBox>(this);
}

void BaseStone::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
	_sound->Dispose();
	_trigger->Dispose();

}

void BaseStone::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);

	myManager = modules.gameStateManager->FindSubManager(L"puzzle_00");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
								{
									DataChangeCallBack(name, value);
								}
	, this);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	Engine::Physics::RigidComponentDesc desc;
	desc.rigidType = Engine::Physics::RigidBodyType::Static;
	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Sphere;
	desc.shapeDesc.geometryDesc.data = { 20.f, _boxScale.y, _boxScale.z, 0 };
	desc.shapeDesc.isExclusive = true;
	desc.shapeDesc.materialDesc.data = { 0.f,0.f,0.f };

	Engine::Transform shapeTransform{};
	PhysicsManager->CreateStatic(&_trigger->_triggerBox, desc, _transform, shapeTransform);
	_trigger->_triggerBox->SetOwner(this);

	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_trigger->_triggerBox);
}

void BaseStone::SendInteractToServer()
{
	_sync->_interactObject.set_objectserialnumber(_sync->GetSerialNumber());
	_sync->_interactObject.SerializeToString(&_sync->_msgBuffer);
	Client::SavePacketData(
		_sync->_msgBuffer, 
		(short)PacketID::InteractObject, 
		_sync->_interactObject.ByteSizeLong(), 
		_sync->GetSerialNumber()
	);
}

void BaseStone::PreSetSoundProperty(std::filesystem::path path)
{
	_sound->SetPath(path);
}

void BaseStone::PostSetSoundProperty(float min, float max)
{
	_sound->SetMinDistance(min);
	_sound->SetMaxDistance(max);
	_sound->SetPosition(_transform.position);
}


