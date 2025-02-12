#include "pch.h"
#include "ServerLogic.h"

bool ServerLogic::Initialize()
{
    bool res = true;
    res = Server::Initialize();
    if (res == false) {
        return false;
    }
    _messageContainer = Server::GetPacketContainer();

    DSH::Time::CreateSystem()(&_system);
    _system->CreateTickTimer(&_timer);
    delete _system;

    _physicsManager = new Engine::PHI::Manager();
    _physicsManager->Initialize(Engine::Physics::PhysicsType::Physx, true);
    //_physicsManager->Initialize(Engine::Physics::PhysicsType::Physx, false);

    //============================
    //  Create Physics Scene
    //============================
    Engine::Physics::SceneDesc sceneDesc{ {0.f, -9.8f, 0.f}, 10 };
    _physicsManager->CreateScene(&_mainScene, sceneDesc);
    _physicsManager->AttachUpdateScene(_mainScene);
    _physicsManager->CreateControllerManager(_mainScene);
    RegistGround(_ground);
    //RegistTrigerBox(_triggerBox);
    //============================

    //============================
    //  Load JSON Data
    //============================
    printf("Start Loading MapData.json...\n");
    _mapData = _jsonLoader.DeSerialize("Assets/Test/MapData.json");
    printf("MapData.json Load Complete.\n");
    LoadStatic();

    LoadQuestData();
    LoadDialogData();
    //============================

    return true;
}

void ServerLogic::Update()
{
    _timer->Tick();
    Server::SendUpdate();
    MessageDispatch();

    // TODO: 내부적으로 업데이트 할 로직을 여기다 넣습니다.
    static float elapsedTime;
    float deltaTime = _timer->GetDeltaTime();
    elapsedTime += deltaTime;

    UpdateObject(deltaTime);
    


    // Fixed Update
    if (elapsedTime >= 0.02f) {
        elapsedTime -= 0.02f;

        SendPositionData();
    } // if end

    Server::SendUpdate();
}

void ServerLogic::Finalize()
{
    for (int i = 0; i < 2; i++) {
        _playerSlot->_controller->Finalize();
    }
    _ground._staticRigid->Finalize();
    _physicsManager->DetachUpdateScene(_mainScene);

    delete _timer;
    Server::Finalize();
    _physicsManager->Finalize();
}

void ServerLogic::MessageDispatch()
{
    if (_messageContainer->empty()) {
        bool res = Server::SwapPacketContainer();
        if (res == false) {
            return;
        }
    }

    while (!_messageContainer->empty()) {
        Packet packet = _messageContainer->front();
        _messageContainer->pop();

        switch ((PacketID)packet._packetId) {
        case PacketID::EnterRequest:
        {
            EnterProcess(packet);
            break;
        } // case end
        case PacketID::Exit:
        {
            ExitProcess(packet);
            break;
        } // case end
        case PacketID::Move:
        {
            MoveProcess(packet);
            break;
        } // case end
        case PacketID::Jump:
        {
            JumpProcess(packet);
            break;
        } // case end
        case PacketID::StateChange:
        {
            StateChangeProcess(packet);
            break;
        } // case end
        case PacketID::PickObject:
        {
            ObjectPickProcess(packet);
            break;
        }
        case PacketID::PutObject:
        {
            ObjectPutProcess(packet);
            break;
        }
        case PacketID::InteractObject:
        {
            ObjectInteractProcess(packet);
            break;
        }
        case PacketID::InteractDialog:
        {
            DialogInteractProcess(packet);
            break;
        }
        case PacketID::DataRequest:
        {
            DataRequestProcess(packet);
            break;
        }
        default:
            break;
        } // switch end
    } // while end
}

// =============================
// Update Function Area
// =============================

void ServerLogic::UpdateObject(float deltaTime)
{
    for (int i = 0; i < 2; i++) {

        //if (_playerSlot[i]._state == 0) {
        //    continue;
        //} // if end
        if (_playerSlot[i]._controller == nullptr) {
            continue;
        } // if end

        _playerSlot[i]._controller->SetDirection(_playerSlot[i]._direction);
        _playerSlot[i]._controller->SetMoveSpeed(_playerSlot[i]._speed);
        _playerSlot[i]._controller->Update(deltaTime);
        _playerSlot[i]._flag = _playerSlot[i]._controller->GetCollisionFlag();
        _playerSlot[i]._controller->FixedUpdate();

        if (_playerSlot[i]._state & (1 << 4) && _playerSlot[i]._controller->IsJump() == false) {
            _stateChange.set_stateinfo(1);
            _stateChange.SerializeToString(&_msgBuffer);
            Server::BroadCast(_msgBuffer, (short)PacketID::StateChange, _stateChange.ByteSizeLong(), _playerSlot[i]._serialNumber);
        }
    } // for end
    _physicsManager->Update(deltaTime);
    _physicsManager->FetchScene();
}
void ServerLogic::SendPositionData()
{
    for (int i = 0; i < 2; i++) {
        if (_playerSlot[i]._controller == nullptr || _playerSlot[i]._state == 0 && (_playerSlot[i]._flag & (unsigned short)Engine::Physics::ControllerCollisionFlag::Down)) {
            continue;
        } // if end
        Engine::Math::Vector3 position = _playerSlot[i]._controller->GetPosition();
        Engine::Math::Quaternion rotation = _playerSlot[i]._rotation;
        //printf("Player%d Position : (%f, %f, %f)\n", i + 1, position.x, position.y, position.z);
        _moveSync.add_position(position.x);
        _moveSync.add_position(position.y);
        _moveSync.add_position(position.z);
        _moveSync.add_rotation(rotation.x);
        _moveSync.add_rotation(rotation.y);
        _moveSync.add_rotation(rotation.z);
        _moveSync.add_rotation(rotation.w);

        _moveSync.SerializeToString(&_msgBuffer);
        Server::BroadCast(_msgBuffer, (short)PacketID::MoveSync, _moveSync.ByteSizeLong(), _playerSlot[i]._serialNumber);
        _moveSync.Clear();
    } // for end

    // TODO: 여기서 업데이트를 진행하는 dynamic object에 대해 위치 정보를 클라이언트로 전송해야 합니다.
}
// =============================

// =============================
// Message Dispatch Area
// =============================

void ServerLogic::EnterProcess(const Packet& packet)
{
    int grantNum = 0;
    for (; grantNum < 2; grantNum++) {
        if (_playerSlot[grantNum]._serialNumber == 0) {
            break;
        } // if end
    } // for end
    if (grantNum == 2) {
        Server::SavePacketData("", packet.sessionId, (short)PacketID::EnterReject, 0, 0);
    } // if end
    else {
        _addObject.set_grantnumber(grantNum + 1);
        _addObject.set_classid("Player");
        _addObject.SerializeToString(&_msgBuffer);
        Server::SavePacketData(_msgBuffer, packet.sessionId, (short)PacketID::EnterAccept, _addObject.ByteSizeLong(), grantNum + 1);

        _playerSlot[grantNum]._serialNumber = grantNum + 1;
        _playerSlot[grantNum]._position = Engine::Math::Vector3(500.0f, 400.0f, 500.0f);
        _playerSlot[grantNum]._sessionId = packet.sessionId;
        // 물리 환경에 등록
        RegistPlayer(&_playerSlot[grantNum]);
        

        printf("[MessageDispatch] Player Enter Accepted. Grant Num : %d\n", grantNum + 1);

        for (int i = 0; i < 2; i++) {
            if (_playerSlot[i]._serialNumber == 0) {
                continue;
            } // if end

            // TODO: 나중에 플레이어 class 타입이 나오면 그 때 수정해야 합니다.
            _addObject.set_grantnumber(_playerSlot[i]._serialNumber);
            _addObject.SerializeToString(&_msgBuffer);

            Server::BroadCast(_msgBuffer, (short)PacketID::Sync, _addObject.ByteSizeLong(), _playerSlot[i]._serialNumber);

        }  // for end
        //for (int i = 0; i < _buildings.size(); i++) {
        //    _addObject.set_grantnumber(_buildings[i]->_serialNumber);
        //    _addObject.set_classid(_buildings[i]->_resourceId);
        //    _addObject.SerializeToString(&_msgBuffer);
        //    Server::SavePacketData(
        //        _msgBuffer,
        //        packet.sessionId,
        //        (short)PacketID::ObjectSync,
        //        _addObject.ByteSizeLong(),
        //        _buildings[i]->_serialNumber
        //    );
        //}
        //for (int i = 0; i < _sudiums.size(); i++) {
        //    _addObject.set_grantnumber(_sudiums[i]->_serialNumber);
        //    _addObject.set_classid(_sudiums[i]->_resourceId);
        //    _addObject.SerializeToString(&_msgBuffer);
        //    Server::SavePacketData(
        //        _msgBuffer,
        //        packet.sessionId,
        //        (short)PacketID::ObjectSync,
        //        _addObject.ByteSizeLong(),
        //        _sudiums[i]->_serialNumber
        //    );
        //}
        //// TODO: 여기서 AddObject에 추가할 오브젝트의 id를 보내는 작업을 수행합니다.
        ////
        //Server::BroadCast("", (short)PacketID::DataSendComplete, 0, 0);
    } // else end
}
void ServerLogic::ExitProcess(const Packet& packet)
{
    unsigned long long exitSessionId = packet.sessionId;

    if (exitSessionId == _playerSlot[0]._sessionId) {
        Server::BroadCast("", (short)PacketID::Exit, 0, _playerSlot[0]._serialNumber);
        _playerSlot[0]._serialNumber = 0;
        _playerSlot[0]._position = Engine::Math::Vector3(0.0f, 0.0f, 0.0f);
        _playerSlot[0]._state = 0;
        _playerSlot[0]._controller->Finalize();
        _playerSlot[0]._controller = nullptr;
        _playerSlot[0]._sessionId = 0;
    }
    else if(exitSessionId == _playerSlot[1]._sessionId) {
        Server::BroadCast("", (short)PacketID::Exit, 0, _playerSlot[1]._serialNumber);
        _playerSlot[1]._serialNumber = 0;
        _playerSlot[1]._position = Engine::Math::Vector3(0.0f, 0.0f, 0.0f);
        _playerSlot[1]._state = 0;
        _playerSlot[1]._controller->Finalize();
        _playerSlot[1]._controller = nullptr;
        _playerSlot[1]._sessionId = 0;
    }
    Server::DeleteSession(packet.sessionId);
}
void ServerLogic::MoveProcess(const Packet& packet)
{
    _move.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));

    int serialNum = packet._serialNumber - 1;

    Engine::Math::Vector3 direction;
    direction.x = _move.x();
    direction.y = _move.y();
    direction.z = _move.z();

    const auto& r = _move.rotation();
    Engine::Math::Quaternion rotation;
    rotation.x = *(r.begin());
    rotation.y = *(r.begin() + 1);
    rotation.z = *(r.begin() + 2);
    rotation.w = *(r.begin() + 3);

    _playerSlot[serialNum]._rotation = rotation;
    _playerSlot[serialNum]._speed = _move.speed();

    if (direction != _playerSlot[serialNum]._direction) {
        _playerSlot[serialNum]._direction = direction;

        Engine::Math::Vector3 position = _playerSlot[serialNum]._controller->GetPosition();
        //printf("Player%d Direction : (%f, %f, %f)\n", serialNum + 1, direction.x, direction.y, direction.z);
        _moveSync.add_position(position.x);
        _moveSync.add_position(position.y);
        _moveSync.add_position(position.z);

        _moveSync.SerializeToString(&_msgBuffer);
        Server::BroadCast(_msgBuffer, (short)PacketID::MoveSync, _moveSync.ByteSizeLong(), packet._serialNumber);
    }
}
void ServerLogic::JumpProcess(const Packet& packet)
{
    _jump.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
    int playerIdx = packet._serialNumber - 1;
    _playerSlot[playerIdx]._controller->Jump(_jump.power() * 5);
}
void ServerLogic::StateChangeProcess(const Packet& packet)
{
    _stateChange.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));

    _playerSlot[packet._serialNumber - 1]._state ^= _stateChange.stateinfo();
    printf("Player%d State Changed. CurrentState : %d\n", packet._serialNumber, _stateChange.stateinfo());
    _stateChange.SerializeToString(&_msgBuffer);
    Server::BroadCast(_msgBuffer, (short)PacketID::StateChange, _stateChange.ByteSizeLong(), packet._serialNumber);
}
void ServerLogic::DataRequestProcess(const Packet& packet)
{
    printf("Start Send Data.\n");
    for (int i = 0; i < 2; i++) {
        if (_playerSlot[i]._serialNumber == 0) {
            continue;
        } // if end

        _syncPlayer.set_x(_playerSlot[i]._position.x);
        _syncPlayer.set_y(_playerSlot[i]._position.y);
        _syncPlayer.set_z(_playerSlot[i]._position.z);
        _syncPlayer.SerializeToString(&_msgBuffer);

        Server::BroadCast(_msgBuffer, (short)PacketID::DataRemote, _syncPlayer.ByteSizeLong(), _playerSlot[i]._serialNumber);
    }  // for end
    
    // Static Object Client Send.

    //for (int i = 0; i < _buildings.size(); i++) {
    //    _syncObject.set_public_(_buildings[i]->_public);
    //    _syncObject.add_position(_buildings[i]->_position.x);
    //    _syncObject.add_position(_buildings[i]->_position.y);
    //    _syncObject.add_position(_buildings[i]->_position.z);
    //    _syncObject.add_rotation(_buildings[i]->_rotation.x);
    //    _syncObject.add_rotation(_buildings[i]->_rotation.y);
    //    _syncObject.add_rotation(_buildings[i]->_rotation.z);
    //    _syncObject.add_rotation(_buildings[i]->_rotation.w);
    //    _syncObject.add_scale(_buildings[i]->_scale.x);
    //    _syncObject.add_scale(_buildings[i]->_scale.y);
    //    _syncObject.add_scale(_buildings[i]->_scale.z);
    //    _syncObject.SerializeToString(&_msgBuffer);
    //    Server::BroadCast(
    //        _msgBuffer,
    //        //packet.sessionId,
    //        (short)PacketID::DataObject,
    //        _syncObject.ByteSizeLong(),
    //        _buildings[i]->_serialNumber
    //    );
    //    _syncObject.Clear();
    //}
    //for (int i = 0; i < _sudiums.size(); i++) {
    //    _syncObject.set_public_(_sudiums[i]->_public);
    //    _syncObject.add_position(_sudiums[i]->_position.x);
    //    _syncObject.add_position(_sudiums[i]->_position.y);
    //    _syncObject.add_position(_sudiums[i]->_position.z);
    //    _syncObject.add_rotation(_sudiums[i]->_rotation.x);
    //    _syncObject.add_rotation(_sudiums[i]->_rotation.y);
    //    _syncObject.add_rotation(_sudiums[i]->_rotation.z);
    //    _syncObject.add_rotation(_sudiums[i]->_rotation.w);
    //    _syncObject.add_scale(_sudiums[i]->_scale.x);
    //    _syncObject.add_scale(_sudiums[i]->_scale.y);
    //    _syncObject.add_scale(_sudiums[i]->_scale.z);
    //    _syncObject.SerializeToString(&_msgBuffer);
    //    Server::BroadCast(
    //        _msgBuffer,
    //        //packet.sessionId,
    //        (short)PacketID::DataObject,
    //        _syncObject.ByteSizeLong(),
    //        _sudiums[i]->_serialNumber
    //    );
    //    _syncObject.Clear();
    //}
    Server::BroadCast("", (short)PacketID::DataSendComplete, 0, 0);
}
void ServerLogic::ObjectPickProcess(const Packet& packet)
{
    _pickObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
    // TODO: Dynamic Object를 찾아서 위치 업데이트를 시작하기 위해 상태를 변경해줘야 합니다.

    _pickObject.SerializeToString(&_msgBuffer);
    Server::BroadCast(
        _msgBuffer,
        (short)PacketID::PickObject,
        _pickObject.ByteSizeLong(),
        _pickObject.targetserialnumber()
    );
}
void ServerLogic::ObjectPutProcess(const Packet& packet)
{
    _putObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
    // TODO: Dynamic Object를 찾아서 위치 업데이트를 종료하기 위해 상태를 변경해줘야 합니다.

    _putObject.SerializeToString(&_msgBuffer);
    Server::BroadCast(
        _msgBuffer,
        (short)PacketID::PutObject,
        _putObject.ByteSizeLong(),
        _putObject.targetserialnumber()
    );
}
void ServerLogic::ObjectInteractProcess(const Packet& packet)
{
    // TODO: 여기서는 오브젝트의 ID에 따라 잡기를 진행하는 부분과 퀘스트 완료와 다이얼로그 시작 로직을 사용해야 합니다.
    _interactObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
    int objectNum = _interactObject.objectserialnumber();
    printf("Object Interact Message. Sender Id : %d, Interact Object Id : %d\n", packet._serialNumber, objectNum);
    // 여기서 해야할 것들.
    // 다이얼로그 띄우기, 퍼즐 클리어(퀘스트 완료), 퍼즐 진행, 
    //

    // ====================
    // Dialog Start Area
    // ====================

    if (objectNum == 10001 && _currentQuestID == 1101) {
        PlayDialog(11501);
    }
    else if (objectNum == 10001 && _currentQuestID == 1103) {
        PlayDialog(11505);
    }
    else if (objectNum == 10002 && _currentQuestID == 2101) {
        PlayDialog(21401);
    }
    else if (objectNum == 10003 && _currentQuestID == 2103) {
        PlayDialog(21605);
    }//
    else if (objectNum == 10004 && _currentQuestID == 3101) {
        PlayDialog(31501);
    }
    else if (objectNum == 10002 && _currentQuestID == 3103) {
        PlayDialog(31306); // 리브 레이 대화
    }
    else if (objectNum == 10004 && _currentQuestID == 3104) {
        PlayDialog(41301);
    }
    else if (objectNum == 10002 && _currentQuestID == 3105) {
        PlayDialog(41204); // 리브 레이 대화
    }
    else if (objectNum == 10004 && _currentQuestID == 1999) {
        PlayDialog(51501);
    }
    else if (objectNum == 10005 && _currentQuestID == 4102) {
        PlayDialog(51705);
    }
    else if (objectNum == 10002 && _currentQuestID == 1999) {
        PlayDialog(61401);
    }
    else if (objectNum == 10003 && _currentQuestID == 5103) {
        PlayDialog(61605);
    }
    //else if (objectNum == 10002 && _currentQuestID == 1103) {
    //    PlayDialog(71601);
    //}
    // ====================

    // ====================
    // Puzzle Clear Area
    // ====================
    
    if (objectNum == 11101) {
        Server::BroadCast("", (short)PacketID::PuzzleSuccess, 0, 1);
        QuestProcess(_currentQuestID);
        printf("[Interact Process] Puzzle Clear. Puzzle Number : %d\n", _currentPuzzleNumber);
    }
    else if (objectNum == 12101) {
        Server::BroadCast("", (short)PacketID::PuzzleSuccess, 0, 1);
        QuestProcess(_currentQuestID);
        printf("[Interact Process] Puzzle Clear. Puzzle Number : %d\n", _currentPuzzleNumber);
    }
    else if (objectNum == 13101) {
        Server::BroadCast("", (short)PacketID::PuzzleSuccess, 0, 1);
        QuestProcess(_currentQuestID);
        printf("[Interact Process] Puzzle Clear. Puzzle Number : %d\n", _currentPuzzleNumber);
    }
    else if (objectNum == 14107) {
        Server::BroadCast("", (short)PacketID::PuzzleSuccess, 0, 1);
        QuestProcess(_currentQuestID);
        printf("[Interact Process] Puzzle Clear. Puzzle Number : %d\n", _currentPuzzleNumber);
    }
    else if (objectNum == 10005) {
        Server::BroadCast("", (short)PacketID::PuzzleSuccess, 0, 1);
        QuestProcess(_currentQuestID);
        _puzzle5Clear = true;
        printf("[Interact Process] Puzzle Clear. Puzzle Number : %d\n", _currentPuzzleNumber);
    }
    // puzzle 6번은 여기서 타는게 아니라 PuzzleProcess에서 타야 할듯.
    else if (objectNum == 6999) {
        Server::BroadCast("", (short)PacketID::PuzzleSuccess, 0, 1);
        QuestProcess(_currentQuestID);
        _puzzle6Clear = true;
        printf("[Interact Process] Puzzle Clear. Puzzle Number : %d\n", _currentPuzzleNumber);
    }
    // ====================

    // ====================
    // Puzzle Play Area
    // ====================
    if (_currentPuzzleNumber == 6) return;
    PuzzleProcess(objectNum);
    // ====================
}
void ServerLogic::DialogInteractProcess(const Packet& packet)
{
    // TODO: 다이얼로그의 현재 ID를 체크하여 다음 다이얼로그로 넘어가거나, 퀘스트의 시작을 알리면 됩니다.
    if (packet._serialNumber == 1) {
        if (!_rayRead) {
            printf("Ray Interacted Dialog.\n");
            _rayRead = true;
        }
    }
    else if (packet._serialNumber == 2) {
        if (!_liveRead) {
            printf("Live Interacted Dialog.\n");
            _liveRead = true;
        }
    }

    if (_rayRead && _liveRead) {
        _interactDialog.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
        int dialogId = _interactDialog.currentdialogid();
        int nextId = _dialogTable[dialogId];
        printf("[DialogProgress] Dialog Next. current : %d, next : %d\n", dialogId, nextId);
        if (nextId == 88888 || nextId == 99999) {
            // 여기서는 다음 퀘스트로 진행 해야함. 다이얼로그의 끝.
            QuestProcess(_currentQuestID);
        }
        else {
            PlayDialog(nextId);
        }
        _rayRead = false;
        _liveRead = false;
    }

    if (_currentQuestID == 1102) {
        Server::BroadCast("", (short)PacketID::PuzzleStart, 0, 1);
        _currentPuzzleNumber++;
        printf("[DialogProgress] Puzzle Start. PuzzleNum : %d\n", _currentPuzzleNumber);
    }
    else if (_currentQuestID == 2102) {
        Server::BroadCast("", (short)PacketID::PuzzleStart, 0, 1);
        _currentPuzzleNumber++;
        printf("[DialogProgress] Puzzle Start. PuzzleNum : %d\n", _currentPuzzleNumber);
    }
    else if (_currentQuestID == 3102) {
        Server::BroadCast("", (short)PacketID::PuzzleStart, 0, 1);
        _currentPuzzleNumber++;
        printf("[DialogProgress] Puzzle Start. PuzzleNum : %d\n", _currentPuzzleNumber);
    }
    else if (_currentQuestID == 3104) {
        Server::BroadCast("", (short)PacketID::PuzzleStart, 0, 1);
        _currentPuzzleNumber++;
        printf("[DialogProgress] Puzzle Start. PuzzleNum : %d\n", _currentPuzzleNumber);
    }
    else if (_currentQuestID == 4102) {
        Server::BroadCast("", (short)PacketID::PuzzleStart, 0, 1);
        _currentPuzzleNumber = 5;
        printf("[DialogProgress] Puzzle Start. PuzzleNum : %d\n", _currentPuzzleNumber);
    }
    else if (_currentQuestID == 5102) {
        Server::BroadCast("", (short)PacketID::PuzzleStart, 0, 1);
        _currentPuzzleNumber = 6;
        printf("[DialogProgress] Puzzle Start. PuzzleNum : %d\n", _currentPuzzleNumber);
    }
}
void ServerLogic::ObjectTriggerProcess(const Packet& packet)
{
    _triggerObject.ParseFromArray(packet._data, PacketDataSize(packet._packetSize));
    int triggerboxId = _triggerObject.triggerboxid();
    int targetObjectId = _triggerObject.objectserialnumber();

    Puzzle6(targetObjectId, triggerboxId);
}
// =============================

// =============================
// JSON Method, Variable Area
// =============================

void ServerLogic::LoadStatic()
{
    printf("Start Loading Building Data...\n");
    const auto& groupData = _mapData["objectGroup"]["groups"];
    for (const auto& staticObject : groupData)
    {
        const auto& objectData = staticObject["models"];
        for (const auto& data : objectData) {
            Object* obj = new Object();
            obj->_resourceId = data["className"].get<std::string>();
            obj->_public = data["publicObject"];

            const auto& transformData = data["transformData"];
            const auto& position = transformData["position"];
            const auto& rotation = transformData["rotation"];
            const auto& scale = transformData["scale"];
            const auto& boxScale = data["boxScale"];
            const auto& boxCentor = data["boxPosition"];
            const auto& isSphere = data["isSphere"];
            obj->_position = Engine::Math::Vector3(position["x"], position["y"], position["z"]);
            obj->_rotation = Engine::Math::Quaternion(Engine::Math::Vector4(rotation["x"], rotation["y"], rotation["z"], rotation["w"]));
            obj->_scale = Engine::Math::Vector3(scale["x"], scale["y"], scale["z"]);
            obj->_boxScale = Engine::Math::Vector3(boxScale["x"], boxScale["y"], boxScale["z"]);
            auto objBoxCentor = Engine::Math::Vector3(boxCentor["x"], boxCentor["y"], boxCentor["z"]);
            printf("Object Load Complete.\n");
            printf("ClassName : %s, \nPosition : (%f, %f, %f), \nRotation : (%f, %f, %f, %f), \nScale : (%f, %f, %f)\n",
                obj->_resourceId.c_str(),
                obj->_position.x, obj->_position.y, obj->_position.z,
                obj->_rotation.z, obj->_rotation.y, obj->_rotation.z, obj->_rotation.w,
                obj->_scale.x, obj->_scale.y, obj->_scale.z
            );
            obj->_serialNumber = _staticObjectSerialNumber++;
            _staticObejcts.push_back(obj);
            Engine::Transform transform{};
            obj->_position *= 10;
            obj->_scale /= 10;
            obj->_boxScale = obj->_boxScale.Split(obj->_scale) * 50.f;
            objBoxCentor *= (obj->_scale);
            objBoxCentor = Engine::Math::Vector3::Transform(objBoxCentor, obj->_rotation);
            objBoxCentor += obj->_position;

            transform.position = objBoxCentor;
            transform.rotation = obj->_rotation;
            if (!isSphere)
                RegistStaticPhysicsBox(*obj, obj->_boxScale);
            else
                RegistStaticPhysicsSphere(*obj, obj->_boxScale);
            obj->_staticRigid->SetTransform(transform);
            printf("_staticObejcts Create Complete. SerialNumber : %d\n", obj->_serialNumber);
        }
    }
    printf("_staticObejcts Data Load Complete.\n");
}


// =============================

// ==============================
// Physics Area
// ==============================

void ServerLogic::RegistDynamicPhysics(Object& obj, Engine::Math::Vector3 scale)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Dynamic;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Capsule;
    rcd.shapeDesc.geometryDesc.data = { scale.x, scale.y, scale.z, 0 };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.5f };

    Engine::Transform tf{};
    tf.position = { 0, 0, 0 };
    _physicsManager->CreateDynamic(&obj._dynamicRigid, rcd, tf, 1);
    _mainScene->AddActor(obj._dynamicRigid);
}

void ServerLogic::RegistStaticPhysicsBox(Object& obj, Engine::Math::Vector3 scale)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Static;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
    rcd.shapeDesc.geometryDesc.data = { scale.x, scale.y, scale.z, 0 };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.f };

    Engine::Transform tf{};
    tf.position = { 0, 0, 0 };
    _physicsManager->CreateStatic(&obj._staticRigid, rcd, tf);
    _mainScene->AddActor(obj._staticRigid);
}

void ServerLogic::RegistStaticPhysicsSphere(Object& obj, Engine::Math::Vector3 scale)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Static;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Sphere;
    rcd.shapeDesc.geometryDesc.data = { scale.x, scale.y, scale.z, 0 };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.f };

    Engine::Transform tf{};
    tf.position = { 0, 0, 0 };
    _physicsManager->CreateStatic(&obj._staticRigid, rcd, tf);
    _mainScene->AddActor(obj._staticRigid);
}

void ServerLogic::RegistPlayer(Player* player)
{
    Engine::Physics::ControllerDesc cd;
    cd.position = Engine::Math::Vector3(0, 0, 0);
    cd.height = 50.f;
    cd.radius = 10.f;
    cd.gravity = { 0.f, -9.8f * 10, 0.f };
    cd.contactOffset = 0.2f;
    cd.stepOffset = 10.f;
    cd.slopeLimit = 0.1f;
    Engine::Physics::IController* controller = player->_controller;
    _physicsManager->CreatePlayerController(&controller, _mainScene, cd);
    player->_controller = static_cast<Engine::Physics::Controller*>(controller);
    player->_controller->SetOwner(&player);
    player->_controller->SetBottomPosition(Engine::Math::Vector3(0.f, 10.f, 0.f));
    player->_controller->Initialize();
    player->_controller->SetPosition(Engine::Math::Vector3(0, 500, 0));
}

void ServerLogic::RegistGround(Ground& ground)
{
    Engine::Physics::GeometryDesc geometryDesc;
    geometryDesc.data = { 2.5f, 2.5f, 6.32f };
    //geometryDesc.data = { 2.5f, 2.5f, 5.f };
    _physicsManager->LoadHeightMap(geometryDesc, "terrain", "Assets/Models/Smoothed_Height_Map.png");
   
    Engine::Transform transform{};
    Engine::Physics::IRigidStaticComponent* staticrigid;
    _physicsManager->CreateTriangleStatic(&staticrigid, "terrain", { {0.0f,0.f,0.f } }, transform);
    ground._staticRigid = static_cast<Engine::Physics::RigidStaticComponent*>(staticrigid);
    _mainScene->AddActor(ground._staticRigid);
    ground._staticRigid->SetTranslate({ -2560.f, -1350.f, -2560.f });
    //ground._staticRigid->SetTranslate({ -2560.f, -1035.f, -2560.f });
    auto tempRotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(-std::numbers::pi_v<float> * 0.5f, 0.f, 0.f);
    ground._staticRigid->SetRotation(tempRotation);

    ground._staticRigid->SetOwner(&ground);
    ground._staticRigid->Initialize();

    Engine::Physics::IRigidComponent* rigid;
    _physicsManager->CreatePlane(&rigid, Engine::Math::Vector3{ 0.f,-60.f, 0 }, Engine::Math::Vector3{ 0.f,1.f, 0 }, { {0.f,0.f,0.f} });
    _mainScene->AddActor(rigid);
}
void ServerLogic::RegistTriggerBox(TriggerBox& triggerBox)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Static;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
    rcd.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.5f };

    Engine::Transform tf{};
    tf.position = { 100, 0.f, 100 };
    Engine::Physics::IRigidStaticComponent* staticRigid;
    _physicsManager->CreateStatic(&staticRigid, rcd, tf);
    triggerBox._staticRigid = static_cast<Engine::Physics::RigidStaticComponent*>(staticRigid);
    triggerBox._staticRigid->SetFlag(Engine::Physics::CollisionType::Collision, false);
    triggerBox._staticRigid->SetFlag(Engine::Physics::CollisionType::Trigger, true);
    _mainScene->AddActor(triggerBox._staticRigid);

    triggerBox._staticRigid->SetOwner(&triggerBox);
    triggerBox._staticRigid->Initialize();
}
// =============================

// =============================
// Quest Logic Area
// =============================
// 퀘스트의 완료 조건
// 1. NPC와의 대화 종료
// 2. 특정 오브젝트와 상호작용
// 
// 퍼즐은 특정 ID의 퀘스트를 받았을 때 활성화 되기 시작함.
// protobuf의 메시지에 퀘스트의 타입을 넣을까?
// 아니면 그냥 퀘스트를 전달하고, 대화창을 띄우거나 퍼즐을 활성화 하라고 메시지를 보낼까?
// 
// 퀘스트의 완료를 클라이언트가 전송.
// 다이얼로그가 종료됐을 때 추가로 퀘스트 넘기기 메시지를 전송
// 오브젝트를 활성화 했을 때 특정 오브젝트의 id를 넘기고 퀘스트 넘기기 메시지를 전송
// 
// 다이얼로그를 넘길 때 현재 다이얼로그 ID를 클라이언트가 전송해서 다음 다이얼로그의 ID를 요청
// 
// 다음 퀘스트를 전달받는 조건은 상호작용을 했을 때.
// 퍼즐 완료 체크를 언제 하는게 좋을지
// 퀘스트를 진행하고 있을 때만 특정 오브젝트가 상호작용이 된다고 단정 짓고 하자.
// 특정 오브젝트를 상호작용 했다는 것은 퀘스트를 확정적으로 완료할 수 있고
// 특정 다이얼로그를 봤다는 것은 퀘스트를 완료할 수 있다는 것이기 때문에
// 그냥 퀘스트 완료를 했다고 클라에 보내야 할까?
// 퀘스트 완료를 보내고, 바로 다음 퀘스트를 보낸다.
// 

void ServerLogic::LoadQuestData()
{
    printf("Start Load QuestData...\n");
    // TODO: 여기서 json을 통해 퀘스트 데이터를 로드해야 합니다.
    json questData = _jsonLoader.DeSerialize("Assets/Test/QuestData.json");
    const auto& questList = questData["QuestData"];
    for (const auto& quest : questList) {
        int requireId = quest["RequireQuestID"];
        int currentId = quest["QuestID"];
        if (requireId == -1) {
            _currentQuestID = currentId;
        }
        else {
            _questTable.insert({ requireId, currentId });
        }
    }
    printf("QuestData Load Complete.\n");
}
void ServerLogic::LoadDialogData()
{
    printf("Start Load DialogData...\n");
    json dialogData = _jsonLoader.DeSerialize("Assets/Test/TestDialog.json");
    const auto& dialogList = dialogData["DialogData"];
    for (const auto& dialog : dialogList) {
        int dialogId = dialog["DialogID"];
        int nextDialogId = dialog["NextDialogID"];
        _dialogTable.insert({ dialogId, nextDialogId });
    }
    printf("DialogData Load Complete.\n");
}
void ServerLogic::QuestProcess(int& questId)
{
    // 여기서는 퀘스트를 진행 시키고, 특정 조건이 만족되면, 퍼즐을 활성화 해야함.
    Server::BroadCast("", (short)PacketID::QuestClear, 0, 0);
    printf("[Quest Process] Quest Clear. Quest Number : %d\n", questId);
    int nextQuestId = _questTable[questId];
    if(questId == 3106 || questId == 4103 || questId == 5103){
        nextQuestId = 1999;
    }
    _questStart.set_questid(nextQuestId);
    _questStart.SerializeToString(&_msgBuffer);
    Server::BroadCast(_msgBuffer, (short)PacketID::QuestStart, _questStart.ByteSizeLong(), 1);
    printf("[Quest Process] Next Quest Start. Quest Number : %d\n", nextQuestId);
    questId = nextQuestId;
}
void ServerLogic::PlayDialog(int dialogId)
{
    _dialogProgress.set_nextdialogid(dialogId);
    _dialogProgress.SerializeToString(&_msgBuffer);
    Server::BroadCast(_msgBuffer, (short)PacketID::PlayDialog, _dialogProgress.ByteSizeLong(), 1);
    printf("[Dialog Progress] Dialog Play Message Send. Dialog Id : %d\n", dialogId);
}
void ServerLogic::PlayDialog(int dialogId, int targetSessionId)
{
    _dialogProgress.set_nextdialogid(dialogId);
    _dialogProgress.SerializeToString(&_msgBuffer);
    Server::SavePacketData(_msgBuffer, targetSessionId, (short)PacketID::PlayDialog, _dialogProgress.ByteSizeLong(), 1);
    printf("[Dialog Progress] Dialog Play Message Send. Dialog Id : %d\n", dialogId);
}
// =============================

// =============================
// Puzzle Area
// =============================

void ServerLogic::PuzzleProcess(int objectId)
{
    switch (_currentPuzzleNumber) {

    case 1:
    {
        Puzzle1(objectId);
        break;
    }
    case 2:
    {
        Puzzle2(objectId);
        break;
    }
    case 3:
    {
        Puzzle3(objectId);
        break;
    }
    case 4:
    {
        Puzzle4(objectId);
        break;
    }
    case 5:
    {
        Puzzle5(objectId);
        break;
    }
    case 6:
    {
        
        break;
    }
    default:
        break;
    }
}
void ServerLogic::Puzzle1(int objectId)
{
    static int curCorrectCount = 0;
    int maxCorrectCount = 3;
    static int activeObjectId = 11103;
    // 리브가 상호작용을 했을 때 이쪽으로 와야함.
    if (objectId == 11107 || objectId == 11108 || objectId == 11109) {
        curCorrectCount++;
        // send puzzleSuccess.
        //_objectActive.set_objectserialnumber(activeObjectId);
        //_objectActive.SerializeToString(&_msgBuffer);
        Server::BroadCast("", (short)PacketID::ObjectActive, 0, activeObjectId++);
        printf("[Puzzle 1] Puzzle Process. curCorrectPuzzle : %d\n", curCorrectCount);
    }
}
void ServerLogic::Puzzle2(int objectId)
{
    // 12102 ~ 12107
    if (objectId == 12108) {
        _soundPlay.set_soundid(101);
        _soundPlay.SerializeToString(&_msgBuffer);
        Server::BroadCast(_msgBuffer, (short)PacketID::SoundPlay, _soundPlay.ByteSizeLong(), 1);
    }
    if (objectId < 12102 && objectId > 12107) {
        return;
    }
    int index = objectId - 12102;
    _balls[index] += _dir[index];
    printf("[Puzzle 2] Cur State  : (%d, %d, %d, %d, %d, %d)\n", _balls[0], _balls[1], _balls[2], _balls[3], _balls[4], _balls[5]);
    _interactObject.set_objectserialnumber(objectId);
    _interactObject.SerializeToString(&_msgBuffer);
    Server::BroadCast(_msgBuffer, (short)PacketID::InteractObject, _interactObject.ByteSizeLong(), objectId);

    if (_balls[index] >= 3 || _balls[index] <= 1) {
        _dir[index] *= -1;
    }

    if (_balls[0] == 1 && _balls[1] == 2 && _balls[2] == 2 && _balls[3] == 3 && _balls[4] == 2 && _balls[5] == 1) {
        //_objectActive.set_objectserialnumber(12101);
        //_objectActive.SerializeToString(&_msgBuffer);
        Server::BroadCast("", (short)PacketID::ObjectActive, 0, 12101);
        printf("[Puzzle 2] Puzzle Clear Object Activated.\n");
    }
}
void ServerLogic::Puzzle3(int objectId)
{
    // 미로 스킵.
}
void ServerLogic::Puzzle4(int objectId)
{
    // 돌 Id : 14102, 14103, 14104, 14106, 14105
    static int activeObjectId = 14201;
    if (objectId == _interactSequence[_currentInteractIndex]) {
        printf("Object Active. Object Num : %d.\n", objectId);
        //_objectActive.set_objectserialnumber(activeObjectId);
        //_objectActive.SerializeToString(&_msgBuffer);
        Server::BroadCast("", (short)PacketID::ObjectActive, 0, activeObjectId++);
    }
    else {
        printf("Puzzle Failed. Reset Object.\n");
        //for (int i = 0; i < _currentInteractIndex; i++) {
        //    _objectDisable.add_objectserialnumber(activeObjectId);
        //}
        //_objectDisable.SerializeToString(&_msgBuffer);
        Server::BroadCast("", (short)PacketID::ObjectDisable, 0, --activeObjectId);
    }
}
void ServerLogic::Puzzle5(int objectId)
{
    // 트리거로만 작동.
}
void ServerLogic::Puzzle6(int objectId, int triggerboxId)
{
    // triggerBox ID : 100100 ~ 100104
    int areaIndex = triggerboxId - 100100;
    int boxIndex = objectId - 16301;
    _currentWeight[areaIndex] += _puzzle6Box[boxIndex];

    if (_currentWeight[areaIndex] == 5) {
        // turn on light.
    }
}
// =============================


