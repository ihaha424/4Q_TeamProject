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
    _physicsManager->Initialize();

    //============================
    //  Create Physics Scene
    //============================
    Engine::Physics::SceneDesc sceneDesc{ {0.f, -9.8f, 0.f}, 10 };
    _physicsManager->CreateScene(&_mainScene, sceneDesc);
    _physicsManager->AttachUpdateScene(_mainScene);
    _physicsManager->CreateControllerManager(_mainScene);
    RegistGround(_ground);
    RegistTrigerBox(_triggerBox);
    //============================

    //============================
    //  Load JSON Data
    //============================
    printf("Start Loading MapData.json...\n");
    _mapData = _jsonLoader.DeSerialize("Assets/Test/MapData.json");
    printf("MapData.json Load Complete.\n");
    LoadBuilding();
    LoadSudium();
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
        printf("Player%d Position : (%f, %f, %f)\n", i + 1, position.x, position.y, position.z);
        _moveSync.set_x(position.x);
        _moveSync.set_y(position.y);
        _moveSync.set_z(position.z);
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
            Server::BroadCast("", (short)PacketID::Sync, 0, _playerSlot[i]._serialNumber);

        }  // for end
        for (int i = 0; i < _buildings.size(); i++) {
            _addObject.set_grantnumber(_buildings[i]->_serialNumber);
            _addObject.set_classid(_buildings[i]->_resourceId);
            _addObject.SerializeToString(&_msgBuffer);
            Server::SavePacketData(
                _msgBuffer,
                packet.sessionId,
                (short)PacketID::ObjectSync,
                _addObject.ByteSizeLong(),
                _buildings[i]->_serialNumber
            );
        }
        for (int i = 0; i < _sudiums.size(); i++) {
            _addObject.set_grantnumber(_sudiums[i]->_serialNumber);
            _addObject.set_classid(_sudiums[i]->_resourceId);
            _addObject.SerializeToString(&_msgBuffer);
            Server::SavePacketData(
                _msgBuffer,
                packet.sessionId,
                (short)PacketID::ObjectSync,
                _addObject.ByteSizeLong(),
                _sudiums[i]->_serialNumber
            );
        }
        // TODO: 여기서 AddObject에 추가할 오브젝트의 id를 보내는 작업을 수행합니다.
        //
        Server::BroadCast("", (short)PacketID::DataSendComplete, 0, 0);
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
    }
    else {
        Server::BroadCast("", (short)PacketID::Exit, 0, _playerSlot[1]._serialNumber);
        _playerSlot[1]._serialNumber = 0;
        _playerSlot[1]._position = Engine::Math::Vector3(0.0f, 0.0f, 0.0f);
        _playerSlot[1]._state = 0;
        _playerSlot[1]._controller->Finalize();
        _playerSlot[1]._controller = nullptr;
    }
    Server::DeleteSession(packet.sessionId);
}
void ServerLogic::MoveProcess(const Packet& packet)
{
    _move.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));

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
        _moveSync.set_x(position.x);
        _moveSync.set_y(position.y);
        _moveSync.set_z(position.z);

        _moveSync.SerializeToString(&_msgBuffer);
        Server::BroadCast(_msgBuffer, (short)PacketID::MoveSync, _moveSync.ByteSizeLong(), packet._serialNumber);
    }
}
void ServerLogic::JumpProcess(const Packet& packet)
{
    _jump.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
    int playerIdx = packet._serialNumber - 1;
    _playerSlot[playerIdx]._controller->Jump(_jump.power() * 5);
}
void ServerLogic::StateChangeProcess(const Packet& packet)
{
    _stateChange.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));

    _playerSlot[packet._serialNumber - 1]._state = _stateChange.stateinfo();
    printf("Player%d State Changed. CurrentState : %d\n", packet._serialNumber, _stateChange.stateinfo());
    _stateChange.SerializeToString(&_msgBuffer);
    Server::BroadCast(_msgBuffer, (short)PacketID::StateChange, _stateChange.ByteSizeLong(), packet._serialNumber);
}
void ServerLogic::DataRequestProcess(const Packet& packet)
{
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
    for (int i = 0; i < _buildings.size(); i++) {
        _syncObject.set_public_(_buildings[i]->_public);
        _syncObject.add_position(_buildings[i]->_position.x);
        _syncObject.add_position(_buildings[i]->_position.y);
        _syncObject.add_position(_buildings[i]->_position.z);
        _syncObject.add_rotation(_buildings[i]->_rotation.x);
        _syncObject.add_rotation(_buildings[i]->_rotation.y);
        _syncObject.add_rotation(_buildings[i]->_rotation.z);
        _syncObject.add_rotation(_buildings[i]->_rotation.w);
        _syncObject.add_scale(_buildings[i]->_scale.x);
        _syncObject.add_scale(_buildings[i]->_scale.y);
        _syncObject.add_scale(_buildings[i]->_scale.z);
        _syncObject.SerializeToString(&_msgBuffer);
        Server::BroadCast(
            _msgBuffer,
            //packet.sessionId,
            (short)PacketID::DataObject,
            _syncObject.ByteSizeLong(),
            _buildings[i]->_serialNumber
        );
        _syncObject.Clear();
    }
    for (int i = 0; i < _sudiums.size(); i++) {
        _syncObject.set_public_(_sudiums[i]->_public);
        _syncObject.add_position(_sudiums[i]->_position.x);
        _syncObject.add_position(_sudiums[i]->_position.y);
        _syncObject.add_position(_sudiums[i]->_position.z);
        _syncObject.add_rotation(_sudiums[i]->_rotation.x);
        _syncObject.add_rotation(_sudiums[i]->_rotation.y);
        _syncObject.add_rotation(_sudiums[i]->_rotation.z);
        _syncObject.add_rotation(_sudiums[i]->_rotation.w);
        _syncObject.add_scale(_sudiums[i]->_scale.x);
        _syncObject.add_scale(_sudiums[i]->_scale.y);
        _syncObject.add_scale(_sudiums[i]->_scale.z);
        _syncObject.SerializeToString(&_msgBuffer);
        Server::BroadCast(
            _msgBuffer,
            //packet.sessionId,
            (short)PacketID::DataObject,
            _syncObject.ByteSizeLong(),
            _sudiums[i]->_serialNumber
        );
        _syncObject.Clear();
    }
    Server::BroadCast("", (short)PacketID::DataSendComplete, 0, 0);
}
void ServerLogic::ObjectPickProcess(const Packet& packet)
{
    _pickObject.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
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
    _putObject.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
    // TODO: Dynamic Object를 찾아서 위치 업데이트를 종료하기 위해 상태를 변경해줘야 합니다.

    _putObject.SerializeToString(&_msgBuffer);
    Server::BroadCast(
        _msgBuffer,
        (short)PacketID::PutObject,
        _putObject.ByteSizeLong(),
        _putObject.targetserialnumber()
    );
}
// =============================

// =============================
// JSON Method, Variable Area
// =============================

void ServerLogic::LoadBuilding()
{
    printf("Start Loading Building Data...\n");
    const auto& groupData = _mapData["objectGroup"]["groups"];
    const auto& buildingData = (*groupData.begin())["models"];
    for (const auto& data : buildingData) {
        Object* obj = new Object();
        obj->_resourceId = data["className"].get<std::string>();
        obj->_public = data["publicObject"];

        const auto& transformData = data["transformData"];
        const auto& position = transformData["position"];
        const auto& rotation = transformData["rotation"];
        const auto& scale = transformData["scale"];
        obj->_position = Engine::Math::Vector3(position["x"], position["y"], position["z"]);
        obj->_rotation = Engine::Math::Quaternion(Engine::Math::Vector4(rotation["x"], rotation["y"], rotation["z"], rotation["w"]));
        obj->_scale = Engine::Math::Vector3(scale["x"], scale["y"], scale["z"]);
        printf("Object Load Complete.\n");
        printf("ClassName : %s, \nPosition : (%f, %f, %f), \nRotation : (%f, %f, %f, %f), \nScale : (%f, %f, %f)\n",
            obj->_resourceId.c_str(),
            obj->_position.x, obj->_position.y, obj->_position.z,
            obj->_rotation.z, obj->_rotation.y, obj->_rotation.z, obj->_rotation.w,
            obj->_scale.x, obj->_scale.y, obj->_scale.z
        );
        obj->_serialNumber = _staticObjectSerialNumber++;
        _buildings.push_back(obj);
        RegistStaticPhysics(*obj);
        Engine::Transform transform{};
        transform.position = obj->_position;
        transform.rotation = obj->_rotation;

        obj->_staticRigid->SetTransform(transform);
    }
    printf("Building Data Load Complete.\n");
}
void ServerLogic::LoadSudium()
{
    printf("Start Loading Sudium Data...\n");
    const auto& groupData = _mapData["objectGroup"]["groups"];
    const auto& sudiumData = (*(groupData.begin() + 1))["models"];
    for (const auto& data : sudiumData) {
        Object* obj = new Object();
        obj->_resourceId = data["className"].get<std::string>();
        obj->_public = data["publicObject"];

        const auto& transformData = data["transformData"];
        const auto& position = transformData["position"];
        const auto& rotation = transformData["rotation"];
        const auto& scale = transformData["scale"];
        obj->_position = Engine::Math::Vector3(position["x"], position["y"], position["z"]);
        obj->_rotation = Engine::Math::Quaternion(Engine::Math::Vector4(rotation["x"], rotation["y"], rotation["z"], rotation["w"]));
        obj->_scale = Engine::Math::Vector3(scale["x"], scale["y"], scale["z"]);
        printf("Object Load Complete.\n");
        printf("ClassName : %s, \nPosition : (%f, %f, %f), \nRotation : (%f, %f, %f, %f), \nScale : (%f, %f, %f)\n",
            obj->_resourceId.c_str(),
            obj->_position.x, obj->_position.y, obj->_position.z,
            obj->_rotation.z, obj->_rotation.y, obj->_rotation.z, obj->_rotation.w,
            obj->_scale.x, obj->_scale.y, obj->_scale.z
        );
        obj->_serialNumber = _staticObjectSerialNumber++;
        _sudiums.push_back(obj);
        RegistStaticPhysics(*obj);
        Engine::Transform transform{};
        transform.position = obj->_position;
        transform.rotation = obj->_rotation;

        obj->_staticRigid->SetTransform(transform);

        printf("Sudium Create Complete. SerialNumber : %d\n", obj->_serialNumber);
    }
    printf("Sudium Data Load Complete.\n");
}
// =============================

// ==============================
// Physics Area
// ==============================

void ServerLogic::RegistDynamicPhysics(Object& obj)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Dynamic;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Capsule;
    rcd.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.5f };

    Engine::Transform tf{};
    tf.position = { 0, 0, 0 };
    _physicsManager->CreateDynamic(&obj._dynamicRigid, rcd, tf, 1);
    _mainScene->AddActor(obj._dynamicRigid);
}

void ServerLogic::RegistStaticPhysics(Object& obj)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Static;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
    rcd.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.5f };

    Engine::Transform tf{};
    tf.position = { 0, 0, 0 };
    _physicsManager->CreateStatic(&obj._staticRigid, rcd, tf);
    _mainScene->AddActor(obj._staticRigid);
}

void ServerLogic::RegistPlayer(Player* player)
{
    Engine::Physics::ControllerDesc cd;
    cd.position = Engine::Math::Vector3(100, 100, 100);
    cd.height = 10.f;
    cd.radius = 2.f;
    cd.gravity = { 0.f, -9.8f * 10, 0.f };
    cd.contactOffset = 0.001f;
    cd.stepOffset = 1.f;
    cd.slopeLimit = 0.707f;
    Engine::Physics::IController* controller = player->_controller;
    _physicsManager->CreatePlayerController(&controller, _mainScene, cd);
    player->_controller = static_cast<Engine::Physics::Controller*>(controller);
    player->_controller->SetBottomPosition({0,10,0});
    player->_controller->SetOwner(&player);
    player->_controller->Initialize();
}

void ServerLogic::RegistGround(Ground& ground)
{
    Engine::Physics::GeometryDesc geometryDesc;
    geometryDesc.data = { 5, 5, 5 };
    _physicsManager->LoadHeightMap(geometryDesc, "terrain", "Assets/Test/test3.png");
    //_physicsManager->LoadTriangleMesh(geometryDesc, "terrain", "Assets/Test/Landscape03.fbx");

    Engine::Transform transform{};
    Engine::Physics::IRigidStaticComponent* staticrigid;
    _physicsManager->CreateTriangleStatic(&staticrigid, "terrain", { {0.f,0.f,0.f } }, transform);
    ground._staticRigid = static_cast<Engine::Physics::RigidStaticComponent*>(staticrigid);
    _mainScene->AddActor(ground._staticRigid);
    ground._staticRigid->SetTranslate({ -1000.f * geometryDesc.data.x, -200.f * geometryDesc.data.y, 1000.f * geometryDesc.data.z });
    //ground._staticRigid->SetTranslate({ 0.f, -1000.f, 0.f });
    //ground._staticRigid->SetRotation(Engine::Math::Quaternion::CreateFromYawPitchRoll(3.14f, 0.f, 0.f));

    ground._staticRigid->SetOwner(&ground);
    ground._staticRigid->Initialize();
}

void ServerLogic::RegistTrigerBox(TriggerBox& triggerBox)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Static;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
    rcd.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.5f };

    Engine::Transform tf{};
    tf.position = { 500, -100.f, 500 };
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