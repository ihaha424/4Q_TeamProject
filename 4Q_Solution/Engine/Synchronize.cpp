#include "pch.h"
#include "Synchronize.h"

Engine::Component::Synchronize::Synchronize() :
	_msgBuffer(std::string(256, '\0'))
{
}

void Engine::Component::Synchronize::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	Engine::Application::GetNetworkManager()->Register(static_cast<Engine::Network::Terminal*>(this));
}

void Engine::Component::Synchronize::Finalize()
{
    Engine::Application::GetNetworkManager()->Unregister(static_cast<Engine::Network::Terminal*>(this));
}

void Engine::Component::Synchronize::InvokeMessage(const Packet& packet)
{
	if (_callbackMap.find(packet._packetId) == _callbackMap.end()) {
		return;
	}

	switch ((PacketID)packet._packetId) {
	case PacketID::EnterAccept:
	{
		_enterAccept.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_enterAccept);
		break;
	}
	case PacketID::Exit:
	{
		_callbackMap[packet._packetId]->Invoke(nullptr);
		break;
	}
	case PacketID::Sync:
	{
		_syncPlayer.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_syncPlayer);
		break;
	}
	case PacketID::ObjectSync:
	{
		_syncObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_syncObject);
		break;
	}
	case PacketID::MoveSync:
	{
		_moveSync.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_moveSync);
		break;
	}
	case PacketID::StateChange:
	{
		_stateChange.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_stateChange);
		break;
	}
	case PacketID::ObjectMove:
	{
		//_objectMove.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		//_callbackMap[packet._packetId]->Invoke(&_objectMove);
		break;
	}
	case PacketID::PickObject:
	{
		_pickObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_pickObject);
		break;
	}
	case PacketID::PutObject:
	{
		_putObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_putObject);
		break;
	}
	case PacketID::PuzzleStart:
	{
		_puzzleStart.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_puzzleStart);
		break;
	}
	case PacketID::PuzzleSuccess:
	{
		_callbackMap[packet._packetId]->Invoke(nullptr);
		break;
	}
	case PacketID::SoundPlay:
	{
		_soundPlay.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_soundPlay);
		break;
	}
	case PacketID::InteractObject:
	{
		_interactObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_interactObject);
		break;
	}
	case PacketID::TriggerObject:
	{
		_triggerObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_triggerObject);
		break;
	}
	case PacketID::PlayDialog:
	{
		_dialogProgress.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_dialogProgress);
		break;
	}
	case PacketID::InteractDialog:
	{
		_interactDialog.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_interactDialog);
		break;
	}
	case PacketID::QuestStart:
	{
		_questStart.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_questStart);
		break;
	}
	case PacketID::QuestClear:
	{
		_questEnd.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_questEnd);
		break;
	}
	case PacketID::ObjectActive:
	{
		_objectActive.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_objectActive);
		break;
	}
	case PacketID::ObjectDisable:
	{
		_objectActive.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_objectActive);
		break;
	}
	case PacketID::DataRemote:
	{
		_syncPlayer.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_syncPlayer);
		break;
	}
	case PacketID::DataObject:
	{
		_syncObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
		_callbackMap[packet._packetId]->Invoke(&_syncObject);
		break;
	}
	case PacketID::ObjectActive:
	{
		_callbackMap[packet._packetId]->Invoke(nullptr);
		break;
	}
	
    default:
        break;
    }
}

void Engine::Component::Synchronize::RemoveCallback(short packetId)
{
    delete _callbackMap[packetId];
    _callbackMap.erase(packetId);
}
