#include "pch.h"
#include "BaseMiniStone.h"

BaseMiniStone::BaseMiniStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	InteractObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath)),
	_gameStateManager(nullptr)
{
}

void BaseMiniStone::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>();
}

void BaseMiniStone::SendInteractToServer()
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

void BaseMiniStone::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void BaseMiniStone::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
}
