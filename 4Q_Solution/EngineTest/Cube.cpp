#include "pch.h"
#include "Cube.h"

Cube::Cube(std::filesystem::path&& meshPath) :
	_meshPath(std::forward<std::filesystem::path>(meshPath)),
	_staticMesh(nullptr),
	_sync(nullptr)
{
}

void Cube::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>();
	_sync = componentFactory->Clone<Engine::Component::SynchronizeComponent>();
}



void Cube::DisposeComponents()
{
	_staticMesh->Dispose();
	_sync->Dispose();
}

void Cube::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_worldMatrix);

	_sync->AddCallback((short)PacketID::DataObject, &Cube::SyncLocation, this);
}

void Cube::PostInitialize(const Engine::Modules& modules)
{
}

void Cube::PostAttach()
{
}

void Cube::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);

	_worldMatrix = Engine::Math::Matrix::CreateScale(1.f) * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);
}

void Cube::PostFixedUpdate()
{
}

void Cube::SyncLocation(const ConnectMsg::SyncObject* msg)
{
	_transform.position = Engine::Math::Vector3(msg->x(), msg->y(), msg->z());
}

void Cube::SetSerialNumber(int num)
{
	_sync->SetSerialNumber(num);
}
