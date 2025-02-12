#include "pch.h"
#include "Obj_Hide_Potion.h"

Obj_Hide_Potion::Obj_Hide_Potion(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: InteractObject(meshPath, meshPath)
{
}

void Obj_Hide_Potion::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Obj_Hide_Potion::SendInteractToServer()
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

void Obj_Hide_Potion::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Hide_Potion::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_04");
	_sync->SetSerialNumber(15101);
}

void Obj_Hide_Potion::Interact()
{
	SendInteractToServer();
	auto data = myManager->GetData(L"Data");
	if (data)
	{
		auto puzzle04 = std::any_cast<Puzzle_04>(data);
		puzzle04._start = true;
		myManager->SetData(L"Data", puzzle04);
		Dispose();
	}
}

void Obj_Hide_Potion::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
