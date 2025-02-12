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
	SendInteractToServer();
}

void Obj_Shinave_Bermiore::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
