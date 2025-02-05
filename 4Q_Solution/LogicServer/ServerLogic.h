#pragma once
#include "Server/ServerEntrance.h"
#include "directxtk/SimpleMath.h"
#include "DSHTime/Time.h"
#include "Physics/InterfaceAPI.h"
#include "../Engine/Math.h"
#include "../Engine/Transform.h"
#include "../Engine/PhysicsUtils.h"
#include "../Engine/Physics.h"
#include "../Engine/PHICoordinateConvert.h"
#include "../Engine/PHIManager.h"
#include "../Packet/PacketID.h"
#include "../Packet/ProtoInclude.h"
#include "JSONLoad.h"


namespace Engine::Physics {
	class Manager;
}

class ServerLogic
{
	struct Object {
		int _serialNumber;
		std::string _resourceId{ "" };
		Engine::Math::Vector3 _position;
		Engine::Math::Vector4 _rotation;
		Engine::Math::Vector3 _scale;
		bool _public;
		Engine::Physics::IRigidStaticComponent* _staticRigid = nullptr;
		Engine::Physics::IRigidDynamicComponent* _dynamicRigid = nullptr;
	};

	struct StaticObject : public Object{

	};

	struct DynamicObject : public Object {

	};

	struct Ground : public Object {
		Engine::Physics::RigidStaticComponent* _staticRigid = nullptr;
	};

	struct TriggerBox : public Object {
		Engine::Physics::RigidStaticComponent* _staticRigid = nullptr;
	};

	struct Player {
		int _serialNumber;
		Engine::Math::Vector3 _position;
		std::string _resourceId;
		Engine::Math::Vector3 _direction;
		int _state;
		float _speed;
		unsigned long long _sessionId;
		Engine::Physics::Controller* _controller = nullptr;
		unsigned short _flag = 0;
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
	std::vector<Object*> _buildings;
	std::vector<Object*> _sudiums;
	TriggerBox _triggerBox{};
	
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
	short _dynamicObjectSerialNumber = 100;
	short _staticObjectSerialNumber = 1000;

private:
	// =============================
	// JSON Method, Variable Area
	// =============================

	JSONLoad _jsonLoader;
	json _mapData;

	void LoadBuilding();
	void LoadSudium();
private:
	// =============================
	// Physics Method, Variable Area
	// =============================

	Engine::Physics::Manager* _physicsManager = nullptr;
	Engine::Physics::IScene* _mainScene = nullptr;

	void RegistDynamicPhysics(Object& obj);
	void RegistStaticPhysics(Object& obj);
	void RegistPlayer(Player* player);
	void RegistGround(Ground& ground);
	void RegistTrigerBox(TriggerBox& triggerBox);
};

