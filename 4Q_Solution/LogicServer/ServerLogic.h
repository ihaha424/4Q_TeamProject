#pragma once
#include "Server/ServerEntrance.h"
#include "directxtk/SimpleMath.h"
#include "DSHTime/Time.h"
#include "Physics/InterfaceAPI.h"
#include "../Engine/Math.h"
#include "../Engine/Transform.h"
#include "../Engine/PhysicsUtils.h"
#include "../Engine/Physics.h"
#include "../Engine/PHIManager.h"
#include "../Packet/PacketID.h"
#include "../Packet/ProtoInclude.h"

namespace Engine::Physics {
	class Manager;
}

class ServerLogic
{


	struct Object {
		int _serialNumber;
		Engine::Math::Vector3 _position;
		std::string _resourceId;

		Engine::Physics::IRigidDynamicComponent* _rigidBody = nullptr;
		
	};

	struct Ground : public Object {
		Engine::Physics::IRigidStaticComponent* _staticRigid = nullptr;
	};

	struct Player : public Object {
		Engine::Math::Vector3 _direction;
		int _state;
		float _speed;
		unsigned long long _sessionId;
		Engine::Physics::Controller* _controller = nullptr;
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
	Engine::Math::Vector3 _lastSendPosition[2]{};
	Object _objs[3]{};
	Ground _ground{};
	
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

private:
	// =============================
	// Physics Method, Variable Area
	// =============================
	Engine::Physics::Manager* _physicsManager = nullptr;
	Engine::Physics::IScene* _mainScene = nullptr;

	void RegistPhysics(Object& obj);
	void RegistPlayer(Player& player);
	void RegistGround(Ground& ground);
};

