#pragma once
#include "Server/ClientEntrance.h"	
#include "../Packet/ProtoInclude.h"

class NetworkTemp
{
public:
	NetworkTemp() = default;

	bool Initialize();
	void Dispatch();

	template <class T, typename... ARGS>
	void AddCallback(short packetId, void(T::*func)(ARGS... args)) {
		if (packetId == (short)PacketID::Sync) {
			_syncCallback = func;
		}
		else if (packetId == (short)PacketID::EnterAccept) {
			_enterSync = func;
		}
	}

private:
	PacketQueue* msgContainer = nullptr;

	std::function<void(float...)> _syncCallback;
	std::function<void(float...)> _enterSync;

	ConnectMsg::EnterAccept _enterAccept;
	ConnectMsg::Exit Exit;
	ConnectMsg::SetRoomMaster _setRoomMaster;
	ConnectMsg::SyncPlayer _syncPlayer;

	MoveMsg::Move _move;
	MoveMsg::Jump _jump;

	PlayMsg::SelectPart _selectPart;
	PlayMsg::InteractDialog _interactDialog;
	PlayMsg::DialogProgress _dialogProgress;
};


