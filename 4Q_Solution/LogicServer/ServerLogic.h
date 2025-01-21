#pragma once
#include "Server/ServerEntrance.h"
#include "DSHTime/Time.h"
#include "../Packet/PacketID.h"
#include "../Packet/ProtoInclude.h"

class ServerLogic
{
	struct Player {
		int _serialNumber;
		float _x;
		float _y;
		float _z;
		int state;
	};

public:
	ServerLogic() = default;
	~ServerLogic() = default;

	bool Initialize();
	void Update();
	void Finalize();


private:
	DSH::Time::ISystem* _system = nullptr;
	DSH::Time::ITickTimer* _timer = nullptr;

	PacketQueue* _messageContainer = nullptr;

	Player _playerSlot[2]{};
	
	ConnectMsg::EnterAccept _enterAccept;
	ConnectMsg::Exit _exit;
	ConnectMsg::SetRoomMaster _setRoomMaster;
	ConnectMsg::SyncPlayer _syncPlayer;
	
	MoveMsg::Move _move;
	MoveMsg::Jump _jump;

	PlayMsg::SelectPart _selectPart;
	PlayMsg::InteractDialog _interactDialog;
	PlayMsg::DialogProgress _dialogProgress;

	std::string _msgBuffer = std::string(256, '\0');

	void MessageDispatch();
};

