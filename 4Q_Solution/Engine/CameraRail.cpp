#include "pch.h"
#include "CameraRail.h"

void Engine::CameraRail::AddControlPoint(const Math::Vector3 position, const Math::Vector3 rotation, const float duration)
{
	AddControlPoint(position, Math::Quaternion::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z), duration);
}

void Engine::CameraRail::AddControlPoint(Math::Vector3 position, Math::Quaternion rotation, float duration)
{
	_controlPoints.emplace_back(position, rotation, duration);
}

Engine::CameraRail::CameraRail() :
	_camera(nullptr),
	_matrix(Math::Matrix::Identity),
	_type(Type::Linear),
	_mode(Mode::Once),
	_state(State::Stopped),
	_direction(Direction::Forward)
{
}

void Engine::CameraRail::Prepare(Content::Factory::Component* componentFactory)
{
	_camera = componentFactory->Clone<Component::Camera>(this);
}

void Engine::CameraRail::PreInitialize(const Modules& modules)
{
	Object::PreInitialize(modules);
	_camera->SetParent(&_matrix);
}

void Engine::CameraRail::PreUpdate(float deltaTime)
{
	Object::PreUpdate(deltaTime);

}

void Engine::CameraRail::DisposeComponents()
{
	_camera->Dispose();
}
