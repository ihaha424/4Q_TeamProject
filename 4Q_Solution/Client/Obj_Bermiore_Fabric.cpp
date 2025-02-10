#include "pch.h"
#include "Obj_Bermiore_Fabric.h"

Obj_Bermiore_Fabric::Obj_Bermiore_Fabric(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	InteractObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void Obj_Bermiore_Fabric::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>();
}

void Obj_Bermiore_Fabric::Interact()
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

void Obj_Bermiore_Fabric::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Bermiore_Fabric::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
}
