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
			for (auto& terminal : _terminalList) {
				_filter(terminal, packet);
			}
		}
	}
}

void Engine::ServerNetwork::Manager::SaveSendData(short packetId, std::string& data, long dataSize, int serialNum)
{
	Client::SavePacketData(data, packetId, dataSize, serialNum);
}
