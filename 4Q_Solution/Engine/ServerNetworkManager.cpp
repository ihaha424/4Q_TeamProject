#include "pch.h"
#include "ServerNetworkManager.h"

Engine::ServerNetwork::Manager::Manager() :
	_filter()
{

}

void Engine::ServerNetwork::Manager::Initialize() 
{
#ifdef CLIENT
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
#else 
	bool res = Server::Initialize();
	if (res == false) {
		printf("[main] Server Initialize Failed. code : %d\n", GetLastError());
		return;
	}
#endif
}

void Engine::ServerNetwork::Manager::Send() 
{
#ifdef CLIENT
	Client::SendUpdate();
#else
	Server::SendUpdate();
#endif
}

void Engine::ServerNetwork::Manager::Receive() 
{
	// Initialize 안에 내부적으로 Recv 진행중. ( 스레드 분리 돼있음 )
}

void Engine::ServerNetwork::Manager::Finalize() 
{
#ifdef CLIENT
	Client::Finalize();
#else
	Server::Finalize();
#endif
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
#ifdef CLIENT
		bool res = Client::SwapPacketContainer();
#else
		bool res = Server::SwapPacketContainer();
#endif
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
#ifdef CLIENT
void Engine::ServerNetwork::Manager::SaveSendData(short packetId, std::string data, long dataSize, int serialNum)
{
	Client::SavePacketData(std::forward<std::string>(data), packetId, dataSize, serialNum);
}
#else
void Engine::ServerNetwork::Manager::SaveSendData(unsigned long long sessionId, short packetId, std::string data, long dataSize, int serialNum)
{
	Server::SavePacketData(data, sessionId, packetId, dataSize, serialNum);
}
void Engine::ServerNetwork::Manager::BroadCast(short packetId, std::string data, long dataSize, int serialNum)
{
	Server::BroadCast(data, packetId, dataSize, serialNum);
}
#endif
void Engine::ServerNetwork::Manager::RegistWorldEvent(short packetId, std::function<void(int)> callback)
{
	_worldCallback.insert({ packetId, callback });
}
