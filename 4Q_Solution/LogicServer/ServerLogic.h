#pragma once
#include "numbers"
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
		Engine::Math::Quaternion _rotation;
		Engine::Math::Vector3 _scale;
		bool _public;
		bool _meshCollider;
		Engine::Math::Vector3 _boxScale;
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

	struct TriggerBox {
		Engine::Physics::RigidStaticComponent* _staticRigid = nullptr;
	};

	struct Player {
		int _serialNumber;
		std::string _resourceId;
		Engine::Math::Vector3 _position;
		Engine::Math::Quaternion _rotation;
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

	Engine::Math::Vector3 _lastSendPosition[2]{};
	Player _playerSlot[2]{};
	Object _objs[3]{};
	Ground _ground{};
	std::vector<Object*> _staticObejcts;
	TriggerBox _triggerBox{};
	
	ConnectMsg::EnterAccept _enterAccept;
	ConnectMsg::SyncPlayer _syncPlayer;
	ConnectMsg::SyncObject _syncObject;
	ConnectMsg::AddObject _addObject;
	
	MoveMsg::Move _move;
	MoveMsg::Jump _jump;
	MoveMsg::MoveSync _moveSync;
	MoveMsg::StateChange _stateChange;
	MoveMsg::ObjectMove _objectMove;

	PlayMsg::SelectPart _selectPart;
	PlayMsg::PickObject _pickObject;
	PlayMsg::PutObject _putObject;
	PlayMsg::SoundPlay _soundPlay;

	PlayMsg::QuestStart _questStart;
	PlayMsg::QuestEnd _questEnd;
	PlayMsg::DialogProgress _dialogProgress;
	PlayMsg::InteractObject _interactObject;
	PlayMsg::InteractDialog _interactDialog;
	PlayMsg::TriggerObject _triggerObject;
	PlayMsg::PuzzleStart _puzzleStart;
	PlayMsg::ObjectActive _objectActive;
	PlayMsg::ObjectDisable _objectDisable;

	std::string _msgBuffer = std::string(256, '\0');

	void MessageDispatch();
private: 
	// =============================
	// Update Function Area
	// =============================

	void UpdateObject(float deltaTime);

	void SendPositionData();

private:
	// =============================
	// Message Dispatch Area
	// =============================

	void EnterProcess(const Packet& packet);
	void ExitProcess(const Packet& packet);
	void MoveProcess(const Packet& packet);
	void JumpProcess(const Packet& packet);
	void StateChangeProcess(const Packet& packet);
	void DataRequestProcess(const Packet& packet);
	void ObjectPickProcess(const Packet& packet);
	void ObjectPutProcess(const Packet& packet);
	void ObjectInteractProcess(const Packet& packet);
	void DialogInteractProcess(const Packet& packet);
	void ObjectTriggerProcess(const Packet& packet);

private:
	// =============================
	// JSON Method, Variable Area
	// =============================

	short _dynamicObjectSerialNumber = 100;
	short _staticObjectSerialNumber = 1000;
	JSONLoad _jsonLoader;
	json _mapData;

	void LoadStatic();
private:
	// =============================
	// Physics Method, Variable Area
	// =============================

	Engine::Physics::Manager* _physicsManager = nullptr;
	Engine::Physics::IScene* _mainScene = nullptr;

	void RegistDynamicPhysics(Object& obj, Engine::Math::Vector3 scale);
	void RegistStaticPhysicsBox(Object& obj, Engine::Math::Vector3 scale);
	void RegistStaticPhysicsSphere(Object& obj, Engine::Math::Vector3 scale);
	void RegistPlayer(Player* player);
	void RegistGround(Ground& ground);
	void RegistTriggerBox(TriggerBox& triggerBox);

private:
	// =============================
	// In Game Logic Area
	// =============================

	enum class QuestState {
		None,
		InProgress,
		Complete
	};

	using QuestID = int;
	using QuestNextTable = std::unordered_map<QuestID, QuestID>;
	using DialogID = int;
	using DialogNextTable = std::unordered_map<DialogID, DialogID>;

	DialogNextTable _dialogTable;
	QuestNextTable _questTable;
	QuestID _currentQuestID = -1;

	bool _rayRead = false;
	bool _liveRead = false;
	bool _puzzle5Clear = false;
	bool _puzzle6Clear = false;

#define DialogMod 10000
#define DialogDiv 1000

	void LoadQuestData();
	void LoadDialogData();
	void QuestProcess(int& questId);
	void PlayDialog(int dialogId);
	void PlayDialog(int dialogId, int targetSessionId);
	// =============================

	// =============================
	// Puzzle Area
	// =============================
	
	int _currentPuzzleNumber = 0;
	// 오브젝트를 상호작용 할 때마다 갱신해줘야함. 
	int _currentInteractObject = -1;



	// Puzzle 1

	// Puzzle 2

	std::vector<int> _balls	{ 1, 1, 1, 1, 1, 1 };
	std::vector<int> _dir	{ 1, 1, 1, 1, 1, 1 };

	// Puzzle 3

	//미로가 나오면 오브젝트 트리거 배치.

	// Puzzle 4

	std::vector<int> _interactSequence{ 14104, 14102, 14106, 14105, 14103 };
	int _currentInteractIndex = 0;

	// Puzzle 5

	// Puzzle 6

	std::vector<int> _currentWeight{ 0, 0, 0, 0, 0 };

	void PuzzleProcess(int objectId);
	void Puzzle1(int objectId);
	void Puzzle2(int objectId);
	void Puzzle3(int objectId);
	void Puzzle4(int objectId);
	void Puzzle5(int objectId);
	void Puzzle6(int objectId);
	
	
	
	
	// =============================


};

