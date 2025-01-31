#include "ServerEntrance.h"
#include "NetworkMain.h"
#include "PacketDispatcher.h"

using namespace Server;

NetworkMain* _mainEntrance = nullptr;
PacketDispatcher* Server::_packetDispatcherInstance = nullptr;

bool SERVER_API Server::Initialize()
{
	_mainEntrance = new NetworkMain();

	bool res = _mainEntrance->Initialize();
	if (res == false) {
		return false;
	}

	_packetDispatcherInstance = PacketDispatcher::GetInstance();

	return true;
}

void SERVER_API Server::Finalize()
{
	_packetDispatcherInstance->DestroyInstance();

	_mainEntrance->Finalize();
	delete _mainEntrance;
	_mainEntrance = nullptr;
}

void SERVER_API Server::SavePacketData(std::string msg, SessionID sid, short packetId, long dataSize, int serialNum)
{
	_packetDispatcherInstance->SaveSendPacket(std::forward<std::string>(msg), sid, packetId, dataSize, serialNum);
}

SERVER_API PacketQueue* Server::GetPacketContainer()
{
	return _packetDispatcherInstance->GetMessageContainer();
}

bool SERVER_API Server::SwapPacketContainer()
{
	return _packetDispatcherInstance->SwapRecvPacketContainer();
}

void SERVER_API Server::SendUpdate()
{
	_mainEntrance->SendUpdate();
}

void SERVER_API Server::BroadCast(std::string msg, short packetId, long dataSize, int serialNum)
{
	_packetDispatcherInstance->SaveBroadCastPacket(std::forward<std::string>(msg), packetId, dataSize, serialNum);
}

void SERVER_API Server::DeleteSession(SessionID sid)
{
	_mainEntrance->Disconnect(sid);
}
