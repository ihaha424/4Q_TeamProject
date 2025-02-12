#include "pch.h"
#include "BG_Terrain.h"
#include "Application.h"


BG_Terrain::BG_Terrain(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: _staticMesh(nullptr), _meshPath(meshPath)
	, _physicsPath{ physicsPath }
{
}

void BG_Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_matrix = _transform.GetMatrix();
	//_matrix = Engine::Math::Matrix::CreateScale(0.1f); /**
	//	Engine::Math::Matrix::CreateFromQuaternion(
	//		Engine::Math::Quaternion::CreateFromYawPitchRoll(std::numbers::pi_v<float>, 0.f, 0.f)) *
	//			Engine::Math::Matrix::CreateTranslation(Engine::Math::Vector3(-100.f, 0.f, 0.f))*/;

	_staticMesh->SetMatrix(&_matrix);
	
	/*const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;	
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) { MoveStarted(); });
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value) { MoveTriggered(value); });*/
}

void BG_Terrain::SetIsPublic(bool isPublic)
{
	_isPublic = isPublic;
}

void BG_Terrain::SetisDynamic(bool isDynamic)
{
	_isDynamic = isDynamic;
}

void BG_Terrain::SetHasMesh(bool hasMesh)
{
	_hasMesh = hasMesh;
}

void BG_Terrain::SetBoxScale(Engine::Math::Vector3 boxScale)
{
}

void BG_Terrain::SetBoxPosition(Engine::Math::Vector3 boxPosition)
{
}

void BG_Terrain::SetIsSphere(bool isSphere)
{
	_isSphere = isSphere;
}

void BG_Terrain::PreUpdate(float deltaTime)
{	
}

void BG_Terrain::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
}

void BG_Terrain::DisposeComponents()
{
	_staticMesh->Dispose();
}

