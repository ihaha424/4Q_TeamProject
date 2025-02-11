#include "pch.h"
#include "BG_Terrain.h"
#include "Application.h"


BG_Terrain::BG_Terrain(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject(meshPath, physicsPath)
{}

void BG_Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	auto pos = _transform.position;
	_transform.scale *= 10;
	_transform.Translate({0.f, 0.f, 0.f});
	_transform.rotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(std::numbers::pi_v<float>, 0.f, 0.f);
	_matrix = _transform.GetMatrix();
	_staticMesh->SetMatrix(&_matrix);


	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.data = { 2.5f, 2.5f, 6.5f };
	PhysicsManager->LoadHeightMap(geometryDesc, "terrain", "Assets/Models/Height_Map.png");

	Engine::Transform transform{};
	PhysicsManager->CreateTriangleStatic(&_rigidStatc->_rigidbody, "terrain", { {0.3f,0.f,0.f } }, transform);
	_rigidStatc->_rigidbody->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidStatc->_rigidbody);
	_rigidStatc->_rigidbody->SetTranslate({ -2560.f, -1450.f, -2560.f });
	auto tempRotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(-std::numbers::pi_v<float> *0.5f, 0.f, 0.f);
	_rigidStatc->_rigidbody->SetRotation(tempRotation);
}

void BG_Terrain::SetIsSphere(bool isShpere)
{
}

void BG_Terrain::PreUpdate(float deltaTime)
{
	//Engine::Input::Device::IKeyboard* keyboard = nullptr;
	//GameClient::Application::GetInputManager()->GetDevice(&keyboard);
	//if (keyboard->IsKeyPressed(Engine::Input::Device::IKeyboard::Key::G))
	//{
	//	_transform.Translate({ 0.f, 10.f, 0.f });
	//}
	//if (keyboard->IsKeyPressed(Engine::Input::Device::IKeyboard::Key::H))
	//{
	//	_transform.Translate({ 0.f, -10.f, 0.f });
	//}
	//_matrix = _transform.GetMatrix();


	//static float Y = -1000.f;
	//GameClient::Application::GetInputManager()->GetDevice(&keyboard);
	//if (keyboard->IsKeyPressed(Engine::Input::Device::IKeyboard::Key::P))
	//{
	//	Y += 10.f;
	//}
	//if (keyboard->IsKeyPressed(Engine::Input::Device::IKeyboard::Key::O))
	//{
	//	Y -= 10.f;
	//}
	//static float Z = -2560.f;
	//GameClient::Application::GetInputManager()->GetDevice(&keyboard);
	//if (keyboard->IsKeyPressed(Engine::Input::Device::IKeyboard::Key::I))
	//{
	//	Z += 10.f;
	//}
	//if (keyboard->IsKeyPressed(Engine::Input::Device::IKeyboard::Key::U))
	//{
	//	Z -= 10.f;
	//}
	//_rigidStatc->_rigidbody->SetTranslate({ Z, Y, Z });
}

