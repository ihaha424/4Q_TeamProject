#include "pch.h"
#include "ServerNetworkManager.h"

Engine::ServerNetwork::Manager::Manager() :
	_filter()
{

}

void Engine::ServerNetwork::Manager::Initialize() 
{
	bool res = Client::Initialize();
	if (res == false) {
		return;
	}
	res = Client::ConnectToServer();
	if (res == false) {
		return;
	}
	
	Client::SavePacketData("", (short)PacketID::EnterRequest, 0, 0);
	Client::SendUpdate();

	_msgContainer = Client::GetPacketContainer();
}

void Engine::ServerNetwork::Manager::Send() 
{
	Client::SendUpdate();
}

void Engine::ServerNetwork::Manager::Receive() 
{
	// Initialize 안에 내부적으로 Recv 진행중. ( 스레드 분리 돼있음 )
}

void Engine::ServerNetwork::Manager::Finalize() 
{
	Client::Finalize();
}

void Engine::ServerNetwork::Manager::Disconnect()
{
	Client::SavePacketData("", (short)PacketID::Exit, 0, 0);
	Client::SendUpdate();
	Client::DisconnectWait();
}

void Engine::ServerNetwork::Manager::Register(Engine::Network::Terminal* terminal)
{
	_terminalList.push_back(terminal);
}

void Engine::ServerNetwork::Manager::Unregister(Engine::Network::Terminal* terminal)
{
	std::list<Engine::Network::Terminal*>::const_iterator it = _terminalList.begin();
	for (; it != _terminalList.end(); it++) {
		if ((*it) == terminal) {
			_terminalList.erase(it);
			break;
		}
	}
}

void Engine::ServerNetwork::Manager::DispatchPacket()
{
	if (_msgContainer->empty()) {
		bool res = Client::SwapPacketContainer();

		if (res == false) {
			return;
		}

		while (!_msgContainer->empty()) {
			Packet packet = _msgContainer->front();
			_msgContainer->pop();

			if (_worldCallback.find(packet._packetId) != _worldCallback.end()) {
				_worldCallback[packet._packetId](packet._serialNumber);
			}

			for (auto& terminal : _terminalList) {
				_filter(terminal, packet);
			}
		}
	}
}

void Engine::ServerNetwork::Manager::SaveSendData(short packetId, std::string data, long dataSize, int serialNum)
{
	Client::SavePacketData(std::forward<std::string>(data), packetId, dataSize, serialNum);
}

void Engine::ServerNetwork::Manager::RegistWorldEvent(short packetId, std::function<void(int)> callback)
{
	_worldCallback.insert({ packetId, callback });
}
