#include "pch.h"
#include "BaseWoolball.h"

BaseWoolball::BaseWoolball(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath) :
	InteractObject(meshPath, meshPath),
	_pos{ 0, -30, -60 }, _index{ 0 }, _activate{ false }, direction{ 1 }
{
}

void BaseWoolball::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void BaseWoolball::SendInteractToServer()
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

void BaseWoolball::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void BaseWoolball::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_01");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
		{
			DataChangeCallBack(name, value);
		}
	, this);
}
