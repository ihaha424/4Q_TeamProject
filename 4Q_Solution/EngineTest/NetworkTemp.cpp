#include "pch.h"
#include "NetworkTemp.h"
#include "../Packet/PacketID.h"

bool NetworkTemp::Initialize()
{
	bool res = true;

	res = Client::Initialize();
	if (res == false) {
		printf("Client Network Initialize Failed. Code : %d\n", GetLastError());
		Client::Finalize();
		return 0;
	}
	msgContainer = Client::GetPacketContainer();

	res = Client::ConnectToServer();
	if (res == false) {
		printf("Server Connect Falied. Code : %d\n", GetLastError());
		Client::Finalize();
		return 0;
	}

	Client::SavePacketData("", (short)PacketID::EnterRequest, 0);

	return true;
}

void NetworkTemp::Dispatch()
{
	if (msgContainer->empty()) {
		bool res = Client::SwapPacketContainer();
		if (res == false) {
			return;
		}
	}

	while (!msgContainer->empty()) {
		Packet packet = msgContainer->front();
		msgContainer->pop();

		switch ((PacketID)packet._packetId) {
		case PacketID::EnterAccept:
		{
			_enterAccept.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));

			curPlayer._serialNumber = _enterAccept.grantnumber();

			break;
		}
		case PacketID::Sync:
		{
			_syncPlayer.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
			if (curPlayer._serialNumber == _syncPlayer.serialnumber()) {
				curPlayer._serialNumber = _syncPlayer.serialnumber();
				curPlayer._x = _syncPlayer.x();
				curPlayer._y = _syncPlayer.y();
				curPlayer._z = _syncPlayer.z();
			}
			else {
				remotePlayer._serialNumber = _syncPlayer.serialnumber();
				remotePlayer._x = _syncPlayer.x();
				remotePlayer._y = _syncPlayer.y();
				remotePlayer._z = _syncPlayer.z();
			}

			break;
		}


		default:
			break;
		}
	}
}
