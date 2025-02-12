#include "pch.h"
#include "BaseStone.h"

BaseStone::BaseStone(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: InteractObject(meshPath, physicsPath)
{
}

void BaseStone::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_sound = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
}

void BaseStone::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
	_sound->Dispose();
}

void BaseStone::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);

	myManager = modules.gameStateManager->FindSubManager(L"puzzle_00");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
								{
									DataChangeCallBack(name, value);
								}
	, this);

}

void BaseStone::SendInteractToServer()
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

void BaseStone::SetSoundProperty(std::filesystem::path path, float min, float max)
{
	_sound->SetPath(path);
	_sound->SetMinDistance(min);
	_sound->SetMaxDistance(max);
}


