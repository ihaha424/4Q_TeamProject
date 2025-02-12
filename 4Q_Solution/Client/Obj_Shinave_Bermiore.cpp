#include "pch.h"
#include "Obj_Shinave_Bermiore.h"

Obj_Shinave_Bermiore::Obj_Shinave_Bermiore(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	InteractObject(meshPath, physicsPath)
{
}

void Obj_Shinave_Bermiore::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Obj_Shinave_Bermiore::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	_sync->SetSerialNumber(11101);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_00");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
		{
			DataChangeCallBack(name, value);
		}
	, this);
}

void Obj_Shinave_Bermiore::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Shinave_Bermiore::SendInteractToServer()
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

void Obj_Shinave_Bermiore::Interact()
{
	if (_activate)
	{
		SendInteractToServer();
	}
}

void Obj_Shinave_Bermiore::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_00>(value);
	if (data._start)
		_activate = true;
	if (data._finish)
		_activate = false;
}
