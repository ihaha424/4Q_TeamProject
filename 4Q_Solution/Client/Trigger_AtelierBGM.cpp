#include "pch.h"
#include "Trigger_AtelierBGM.h"

void Trigger_AtelierBGM::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_trigger = componentFactory->Clone<TriggerBox>(this);
	_sound = componentFactory->Clone<Engine::Component::EffectSound>(this);
}


void Trigger_AtelierBGM::SetIsPublic(bool isPublic)
{
	_isPublic = isPublic;
}

void Trigger_AtelierBGM::SetisDynamic(bool isDynamic)
{
	_isDynamic = isDynamic;
}

void Trigger_AtelierBGM::SetHasMesh(bool hasMesh)
{
	_hasMesh = hasMesh;
}

void Trigger_AtelierBGM::SetBoxScale(Engine::Math::Vector3 boxScale)
{
	_boxScale = boxScale;
}

void Trigger_AtelierBGM::SetBoxPosition(Engine::Math::Vector3 boxPosition)
{
	_boxPosition = boxPosition;
}

void Trigger_AtelierBGM::SetIsSphere(bool isSphere)
{
	_isSphere = isSphere;
}

void Trigger_AtelierBGM::DisposeComponents()
{
	_trigger->Dispose();
	_sound->Dispose();
}

void Trigger_AtelierBGM::PreInitialize(const Engine::Modules& modules)
{
	_sound->SetPath(L"Assets/Sounds/BGM_Bermiore.wav");
	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	Engine::Math::Vector3 positionData = { -89.f, 15.f, -76.f };
	Engine::Math::Vector3 scaleData = { 1.f, 1.f, 1.f };
	Engine::Math::Vector3 boxScaleData = { 80.f, 0.f, 0.f };

	positionData *= 10;
	scaleData /= 10;
	boxScaleData = boxScaleData.Split(scaleData) * 50.f;
	_transform.position = positionData;

	Engine::Physics::RigidComponentDesc desc;
	desc.rigidType = Engine::Physics::RigidBodyType::Static;
	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Sphere;
	desc.shapeDesc.geometryDesc.data = { boxScaleData.x, boxScaleData.y, boxScaleData.z, 0 };
	desc.shapeDesc.isExclusive = true;
	desc.shapeDesc.materialDesc.data = { 0.f,0.f,0.f };

	Engine::Transform shapeTransform{};
	PhysicsManager->CreateStatic(&_trigger->_triggerBox, desc, _transform, shapeTransform);
	_trigger->_triggerBox->SetOwner(this);

	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_trigger->_triggerBox);

	_trigger->BindBeginInteraction([this]() {
		_sound->Play();
		});
}
