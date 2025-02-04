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
    //============================

    _objs[0]._position = { 100.f, 0.f, 100.f };
    _objs[1]._position = { 500.f, 0.f, 300.f };
    _objs[2]._position = { -100.f, 0.f, 500.f };

    _objs[0]._resourceId = "../Resources/TestObject/cube.fbx";
    _objs[1]._resourceId = "../Resources/TestObject/cube.fbx";
    _objs[2]._resourceId = "../Resources/TestObject/cube.fbx";

    _objs[0]._serialNumber = 100;
    _objs[1]._serialNumber = 101;
    _objs[2]._serialNumber = 102;

    return true;
}

void ServerLogic::Update()
{
    _timer->Tick();

    MessageDispatch();

    // TODO: 내부적으로 업데이트 할 로직을 여기다 넣습니다.
    static float elapsedTime;
    elapsedTime += _timer->GetDeltaTime();

    static unsigned short collisionFlg;

    for (int i = 0; i < 2; i++) {

        //if (_playerSlot[i]._state == 0) {
        //    continue;
        //} // if end
        if (_playerSlot[i]._controller == nullptr) {
            continue;
        } // if end

        _playerSlot[i]._controller->SetVelocity(_playerSlot[i]._direction * _playerSlot[i]._speed);
        _playerSlot[i]._controller->Update(_timer->GetDeltaTime());
        _playerSlot[i]._flag = _playerSlot[i]._controller->GetCollisionFlag();

    } // for end
    _physicsManager->Update(_timer->GetDeltaTime());
    _physicsManager->FetchScene();

    if (elapsedTime >= 0.02f) {
        elapsedTime -= 0.02f;
        for (int i = 0; i < 2; i++) {
            if (_playerSlot[i]._controller == nullptr || _playerSlot[i]._state == 0 && (collisionFlg & (unsigned short)Engine::Physics::ControllerCollisionFlag::Down)) {
                continue;
            } // if end
            Engine::Math::Vector3 position = _playerSlot[i]._controller->GetPosition();
            printf("Player%d Position : (%f, %f, %f)\n", i + 1, position.x, position.y, position.z);
            _moveSync.set_x(position.x);
            _moveSync.set_y(position.y);
            _moveSync.set_z(position.z);

            _moveSync.SerializeToString(&_msgBuffer);
            Server::BroadCast(_msgBuffer, (short)PacketID::MoveSync, _moveSync.ByteSizeLong(), _playerSlot[i]._serialNumber);
        } // for end
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
                _enterAccept.set_grantnumber(grantNum + 1);
                _enterAccept.SerializeToString(&_msgBuffer);
                Server::SavePacketData(_msgBuffer, packet.sessionId, (short)PacketID::EnterAccept, _enterAccept.ByteSizeLong(), grantNum + 1);

                _playerSlot[grantNum]._serialNumber = grantNum + 1;
                _playerSlot[grantNum]._position = Engine::Math::Vector3(0.0f, 400.0f, 0.0f);
                _playerSlot[grantNum]._sessionId = packet.sessionId;
                // 물리 환경에 등록
                RegistPlayer(_playerSlot[grantNum]);

                printf("[MessageDispatch] Player Enter Accepted. Grant Num : %d\n", grantNum + 1);

                for (int i = 0; i < 2; i++) {
                    if (_playerSlot[i]._serialNumber == 0) {
                        continue;
                    } // if end
                    Server::BroadCast("", (short)PacketID::Sync, 0, _playerSlot[i]._serialNumber);
                }  // for end
                for (int i = 0; i < 3; i++) {
                    Server::BroadCast("", (short)PacketID::ObjectSync, 0, _objs[i]._serialNumber);
                }
                Server::BroadCast("", (short)PacketID::DataSendComplete, 0, 0);
            } // else end
            break;
        } // case end
        case PacketID::Exit:
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

            break;
        } // case end
        case PacketID::ExitOk:
        {
            // TODO: 여기서 해당하는 클라이언트의 세션을 제거해야 합니다.

            break;
        } // case end
        case PacketID::Move:
        {
            _move.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
            
            int serialNum = packet._serialNumber - 1;

            Engine::Math::Vector3 direction;
            direction.x = _move.x();
            direction.y = _move.y();
            direction.z = _move.z();
            _playerSlot[serialNum]._speed = _move.speed();

            if (direction != _playerSlot[serialNum]._direction) {
                _playerSlot[serialNum]._direction = direction;

                Engine::Math::Vector3 position = _playerSlot[serialNum]._controller->GetPosition();
                printf("Player%d Position : (%f, %f, %f)\n", serialNum + 1, position.x, position.y, position.z);
                _moveSync.set_x(position.x);
                _moveSync.set_y(position.y);
                _moveSync.set_z(position.z);



                _moveSync.SerializeToString(&_msgBuffer);
                Server::BroadCast(_msgBuffer, (short)PacketID::MoveSync, _moveSync.ByteSizeLong(), packet._serialNumber);
            }

            break;
        } // case end
        case PacketID::Jump:
        {
            _jump.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));
            int playerIdx = packet._serialNumber - 1;
            _playerSlot[playerIdx]._controller->SetGravity({ 0.f, _jump.power(), 0.f });

            break;
        } // case end
        case PacketID::StateChange:
        {
            _stateChange.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));

            _playerSlot[packet._serialNumber - 1]._state = _stateChange.stateinfo();
            printf("Player%d State Changed. CurrentState : %d\n", packet._serialNumber - 1, _stateChange.stateinfo());
            _stateChange.SerializeToString(&_msgBuffer);
            Server::BroadCast(_msgBuffer, (short)PacketID::StateChange, _stateChange.ByteSizeLong(), packet._serialNumber);

            break;
        } // case end
        case PacketID::DataRequest:
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
            for (int i = 0; i < 3; i++) {
                _syncObject.set_x(_objs[i]._position.x);
                _syncObject.set_y(_objs[i]._position.y);
                _syncObject.set_z(_objs[i]._position.z);
                _syncObject.SerializeToString(&_msgBuffer);

                Server::BroadCast(_msgBuffer, (short)PacketID::DataObject, _syncObject.ByteSizeLong(), _objs[i]._serialNumber);
            }
            Server::BroadCast("", (short)PacketID::DataSendComplete, 0, 0);

            break;
        }
        default:
            break;
        } // switch end
    } // while end
}


// ==============================
// Physics Area
// ==============================
void ServerLogic::RegistPhysics(Object& obj)
{
    Engine::Physics::RigidComponentDesc rcd;
    rcd.rigidType = Engine::Physics::RigidBodyType::Dynamic;
    rcd.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Capsule;
    rcd.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
    rcd.shapeDesc.isExclusive = true;
    rcd.shapeDesc.materialDesc.data = { 0.5f, 0.5f, 0.5f };

    Engine::Transform tf{};
    tf.position = { 0, 0, 0 };
    _physicsManager->CreateDynamic(&obj._rigidBody, rcd, tf, 1);
    _mainScene->AddActor(obj._rigidBody);
}

void ServerLogic::RegistPlayer(Player& player)
{
    Engine::Physics::ControllerDesc cd;
    cd.height = 10.f;
    cd.radius = 2.f;
    cd.gravity = { 0.f, -0.98f, 0.f };
    cd.contactOffset = 3.f;
    cd.stepOffset = 2.f;
    cd.slopeLimit = 0.5f;
    Engine::Physics::IController* controller = player._controller;
    _physicsManager->CreatePlayerController(&controller, _mainScene, cd);
    player._controller = static_cast<Engine::Physics::Controller*>(controller);
}

void ServerLogic::RegistGround(Ground& ground)
{
    Engine::Physics::GeometryDesc geometryDesc;
    geometryDesc.data = { 1, 1, 1 };
    _physicsManager->LoadHeightMap(geometryDesc, "terrain", "../Resources/Terrain/testTest.png");

    Engine::Transform transform{};
    _physicsManager->CreateTriangleStatic(&ground._staticRigid, "terrain", { {0.f,0.f,0.f } }, transform);
    _mainScene->AddActor(ground._staticRigid);
    ground._staticRigid->SetTranslate({ -1000.f, -200.f, 1000.f });

}
