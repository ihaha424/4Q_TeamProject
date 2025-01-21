#include "ClientEntrance.h"
#include "ClientNetwork.h"
#include "PacketDispatcher.h"

using namespace Client;

ClientNetwork* _mainEntrance = nullptr;
PacketDispatcher* Client::_packetDispatcherInstance = nullptr;

bool SERVER_API Client::Initialize()
{
	_mainEntrance = new ClientNetwork();

	bool res = _mainEntrance->Initialize();
	if (res == false) {
		return false;
	}

	_packetDispatcherInstance = PacketDispatcher::GetInstance();

	return true;
}

void SERVER_API Client::Finalize()
{
	_packetDispatcherInstance->DestroyInstance();

	_mainEntrance->Finalize();
	delete _mainEntrance;
	_mainEntrance = nullptr;
}

void SERVER_API Client::SavePacketData(std::string msg, short packetId, long dataSize)
{
	_packetDispatcherInstance->SaveBroadCastPacket(msg, packetId, dataSize);
}

SERVER_API PacketQueue* Client::GetPacketContainer()
{
	return _packetDispatcherInstance->GetMessageContainer();
}

bool SERVER_API Client::SwapPacketContainer()
{
	return _packetDispatcherInstance->SwapRecvPacketContainer();
}

void SERVER_API Client::SendUpdate()
{
	_mainEntrance->SendUpdate();
}

bool SERVER_API Client::ConnectToServer()
{
	return _mainEntrance->ConnectToServer();
}
