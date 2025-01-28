#pragma once
#include "Server/ServerEntrance.h"
#include "DSHTime/Time.h"
#include "../Packet/PacketID.h"
#include "../Packet/ProtoInclude.h"

class ServerLogic
{
	struct Vector3 {
		float _x;
		float _y;
		float _z;
		Vector3 operator*(float f) {
			return Vector3(_x * f, _y * f, _z * f);
		}
		Vector3 operator+(Vector3& v) {
			return Vector3(_x + v._x, _y + v._y, _z + v._z);
		}
		bool operator!=(Vector3& v) {
			return (_x != v._x) || (_y != v._y) || (_z != v._z);
		}
	};

	struct Object {
		int _serialNumber;
		Vector3 _position;
		std::string _resourceId;
	};

	struct Player : public Object {
		Vector3 _direction;
		int _state;
		float _speed;
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
	Vector3 _lastSendPosition[2]{};
	Object _objs[3]{};
	
	ConnectMsg::EnterAccept _enterAccept;
	ConnectMsg::SyncPlayer _syncPlayer;
	ConnectMsg::SyncObject _syncObject;
	ConnectMsg::AddObject _addObject;
	ConnectMsg::AddRemote _addRemote;
	
	MoveMsg::Move _move;
	MoveMsg::Jump _jump;
	MoveMsg::MoveSync _moveSync;
	MoveMsg::StateChange _stateChange;

	PlayMsg::SelectPart _selectPart;
	PlayMsg::InteractDialog _interactDialog;
	PlayMsg::DialogProgress _dialogProgress;

	std::string _msgBuffer = std::string(256, '\0');

	void MessageDispatch();
};

