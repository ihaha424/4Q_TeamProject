#include "pch.h"
#include "GameCoreData.h"
#include "Application.h"

GameCoreObject::GameCoreObject()
	: _sync{ nullptr }
{
}

void GameCoreObject::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void GameCoreObject::DisposeComponents()
{
	Engine::Object::Dispose();
	_sync->Dispose();
}

void GameCoreObject::PreInitialize(const Engine::Modules& modules)
{
	Engine::Object::PreInitialize(modules);
}

void GameCoreObject::SendInteractToServer()
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
