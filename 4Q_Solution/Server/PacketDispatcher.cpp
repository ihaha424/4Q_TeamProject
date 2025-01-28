#include "PacketDispatcher.h"
#include "GlobalDef.h"
#include "Packet.h"
#include "Utils/StreamBuffer.h"

ImplSingleton(PacketDispatcher)

void PacketDispatcher::SaveRecvPacket(StreamBuffer* recvData, SessionID sid)
{
	while (true) {
		PacketHeader header;
		bool res = recvData->Peek(PtrCast(char*, &header), sizeof(PacketHeader));
		if (res == false) {
			//printf("[Dispatcher::SaveRecvPacket] Packet Header Peek Failed.\n");
			return;
		}
		//printf("[Dispatcher::SaveRecvPacket] Packet Header Peek Success.\n");

		if ((int)header._packetSize > recvData->Size()) {
			//printf("[Dispatcher::SaveRecvPacket] Packet Data Not Complete. PacketSize : %d, StreamBuffer Size : %d\n", header._packetSize, recvData->Size());
			return;
		}

		Packet packet;
		recvData->Read(PtrCast(char*, &packet), (int)header._packetSize);
		packet.sessionId = sid;
		//printf("[Dispatcher::SaveRecvPacket] Packet Get. Size : %d\n", (int)header._packetSize);
		Lock lock(_recvMtx);
		_saveRecvContainer.push(std::move(packet));
	}
}

bool PacketDispatcher::SwapRecvPacketContainer()
{
	Lock lock(_recvMtx);
	if (_saveRecvContainer.empty()) {
		return false;
	}

	std::swap(_saveRecvContainer, _dispatchMessageContainer);

	return true;
}

void PacketDispatcher::SaveSendPacket(std::string& data, SessionID sid, short packetId, long dataSize, int serialNum)
{
	Packet packet;
	MakePacket(packet, data, sid, packetId, dataSize, serialNum);

	Lock lock(_sendMtx);
	_saveSendContainer[sid].push(packet);
}

bool PacketDispatcher::SwapSendPacketContainer(SessionID sid)
{
	Lock lock(_sendMtx);
	if (_saveSendContainer[sid].empty()) {
		return false;
	}

	std::swap(_saveSendContainer[sid], _sessionSendContainer[sid]);

	return true;
}

PacketQueue* PacketDispatcher::GetMessageContainer()
{
	return &_dispatchMessageContainer;
}

SendQueue* PacketDispatcher::GetSendMessageContainer(SessionID sid)
{
	return &(_sessionSendContainer[sid]);
}

void PacketDispatcher::SessionCreated(SessionID sid)
{
	Lock lock(_sendMtx);
	_sessionSendContainer.insert({ sid, SendQueue() });
	_saveSendContainer.insert({ sid, SendQueue() });
}

void PacketDispatcher::SaveBroadCastPacket(std::string& data, short packetId, long dataSize, int serialNum)
{
	for (auto& [sid, packetContainer] : _saveSendContainer) {
		Packet packet;
		MakePacket(packet, data, sid, packetId, dataSize, serialNum);

		Lock lock(_sendMtx);
		packetContainer.push(packet);
	}
}

void PacketDispatcher::MakePacket(Packet& packet, std::string& data, SessionID sid, short packetId, long dataSize, int serialNum)
{
	packet.sessionId = sid;
	packet._packetId = packetId;
	packet._serialNumber = serialNum;

	memcpy(packet._data, data.c_str(), dataSize);
	packet._packetSize = sizeof(PacketHeader) + dataSize;
}
