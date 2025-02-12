#include "pch.h"
#include "Obj_Shinave_Platform_Spawn_1.h"

Obj_Shinave_Platform_Spawn_1::Obj_Shinave_Platform_Spawn_1(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject(meshPath, physicsPath)
{
}

void Obj_Shinave_Platform_Spawn_1::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	StaticObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Obj_Shinave_Platform_Spawn_1::SetActive(const PlayMsg::ObjectActive* msg)
{
	auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
	if (!isData)
		return;
	auto data = std::any_cast<GameCoreData>(*isData);
	if (data.player == 1 || data.player == 3)
	{
		_staticMesh->SetActiveDraw(true);
	}
}

void Obj_Shinave_Platform_Spawn_1::DisposeComponents()
{
	StaticObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Shinave_Platform_Spawn_1::PreInitialize(const Engine::Modules& modules)
{
	StaticObject::PreInitialize(modules);
	_sync->AddCallback((short)PacketID::ObjectActive, &Obj_Shinave_Platform_Spawn_1::SetActive, this);
	_sync->SetSerialNumber(11103);
}

void Obj_Shinave_Platform_Spawn_1::PostInitialize(const Engine::Modules& modules)
{
	_staticMesh->SetActiveDraw(false);
}
