#include "pch.h"
#include "SynchronizeComponent.h"

Engine::Component::SynchronizeComponent::SynchronizeComponent() :
	_msgBuffer(std::string(256, '\0'))
{
}

void Engine::Component::SynchronizeComponent::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	Engine::Application::GetNetworkManager()->Register(static_cast<Engine::Network::Terminal*>(this));
}

void Engine::Component::SynchronizeComponent::Finalize()
{
    Engine::Application::GetNetworkManager()->Unregister(static_cast<Engine::Network::Terminal*>(this));
}

void Engine::Component::SynchronizeComponent::InvokeMessage(const Packet& packet)
{
    switch ((PacketID)packet._packetId) {
    case PacketID::EnterAccept:
    {
        _enterAccept.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
        _callbackMap[packet._packetId]->Invoke(&_enterAccept);
        break;
    }
	//case PacketID::Sync:
	//{
	//	_callbackMap[packet._packetId]->Invoke(&_syncPlayer);

	//	break;
	//}
	case PacketID::MoveSync:
	{
		_moveSync.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
		_callbackMap[packet._packetId]->Invoke(&_moveSync);
		break;
	}
	case PacketID::StateChange:
	{
		_stateChange.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
		_callbackMap[packet._packetId]->Invoke(&_stateChange);
		break;
	}

    default:
        break;
    }
}

void Engine::Component::SynchronizeComponent::RemoveCallback(short packetId)
{
    delete _callbackMap[packetId];
    _callbackMap.erase(packetId);
}
