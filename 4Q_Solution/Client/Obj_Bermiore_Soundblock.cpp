#include "pch.h"
#include "Obj_Bermiore_Soundblock.h"

Obj_Bermiore_Soundblock::Obj_Bermiore_Soundblock(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: InteractObject(meshPath, meshPath), _sync{ nullptr }
{
}

void Obj_Bermiore_Soundblock::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Obj_Bermiore_Soundblock::SendInteractToServer()
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

void Obj_Bermiore_Soundblock::PlaySound()
{

}

void Obj_Bermiore_Soundblock::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Bermiore_Soundblock::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_01");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
{
			DataChangeCallBack(name, value);
		}
	, this);
	//_sync->AddCallback((short)PacketID::ObjectActive, &Obj_Bermiore_Soundblock::PlaySound, this);
	//_sync->SetSerialNumber(12108);
}

void Obj_Bermiore_Soundblock::Interact()
{
	SendInteractToServer();
}

void Obj_Bermiore_Soundblock::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
