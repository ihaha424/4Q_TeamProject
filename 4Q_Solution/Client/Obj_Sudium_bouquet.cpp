#include "pch.h"
#include "Obj_Sudium_bouquet.h"

Obj_Sudium_bouquet::Obj_Sudium_bouquet(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	InteractObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath)),
	_gameStateManager(nullptr)
{
	_index = 0;
}
void Obj_Sudium_bouquet::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>();
}

void Obj_Sudium_bouquet::Interact()
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

void Obj_Sudium_bouquet::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Sudium_bouquet::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
}
