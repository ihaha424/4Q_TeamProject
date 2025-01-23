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

    return true;
}

void ServerLogic::Update()
{
    _timer->Tick();

    MessageDispatch();

    // TODO: 내부적으로 업데이트 할 로직을 여기다 넣습니다.
    static float elapsedTime;
    elapsedTime += _timer->GetDeltaTime();

    for (int i = 0; i < 2; i++) {
        // player idle
        //if (_playerSlot[i]._state == 0) {
        //    continue;
        //} // if end
        //Vector3 velocity = _playerSlot[i]._direction * _playerSlot[i]._speed * _timer->GetDeltaTime();
        //_playerSlot[i]._position = _playerSlot[i]._position + velocity;
        if (_playerSlot[i]._serialNumber == 0) continue;
        if (elapsedTime >= 0.01f) {
            elapsedTime -= 0.01f;
            _moveSync.set_serialnumber(i + 1);
            _moveSync.set_x(_playerSlot[i]._position._x);
            _moveSync.set_y(_playerSlot[i]._position._y);
            _moveSync.set_z(_playerSlot[i]._position._z);

            _moveSync.SerializeToString(&_msgBuffer);
            Server::BroadCast(_msgBuffer, (short)PacketID::MoveSync, _moveSync.ByteSizeLong());
        }
        //if (i == 0) {
        //    //printf("MovePlayer Position : %f, %f, %f\n", _playerSlot[i]._position._x, _playerSlot[i]._position._y, _playerSlot[i]._position._z);
        //}
    } // for end

    Server::SendUpdate();
}

void ServerLogic::Finalize()
{
    delete _timer;
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
                Server::SavePacketData("", packet.sessionId, (short)PacketID::EnterReject, 0);
            } // if end
            else {
                _enterAccept.set_grantnumber(grantNum + 1);
                _enterAccept.SerializeToString(&_msgBuffer);
                Server::SavePacketData(_msgBuffer, packet.sessionId, (short)PacketID::EnterAccept, _enterAccept.ByteSizeLong());

                _playerSlot[grantNum]._serialNumber = grantNum + 1;
                _playerSlot[grantNum]._position = Vector3(0.0f, 0.0f, 0.0f);

                printf("[MessageDispatch] Player Enter Accepted. Grant Num : %d\n", grantNum + 1);

                for (int i = 0; i < 2; i++) {
                    if (_playerSlot[i]._serialNumber == 0) {
                        continue;
                    } // if end
                    _syncPlayer.set_serialnumber(_playerSlot[i]._serialNumber);
                    _syncPlayer.set_x(_playerSlot[i]._position._x);
                    _syncPlayer.set_y(_playerSlot[i]._position._y);
                    _syncPlayer.set_z(_playerSlot[i]._position._z);

                    long byteSize = _syncPlayer.ByteSizeLong();

                    _syncPlayer.SerializeToString(&_msgBuffer);
                    Server::BroadCast(_msgBuffer, (short)PacketID::Sync, _syncPlayer.ByteSizeLong());
                }  // for end
            } // else end
            break;
        } // case end
        case PacketID::Exit:
        {
            _exit.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));

            int exitNum = _exit.serialnumber();

            _playerSlot[exitNum]._serialNumber = 0;
            _playerSlot[exitNum]._position = Vector3(0.0f, 0.0f, 0.0f);
            _playerSlot[exitNum]._state = 0;

            _exit.SerializeToString(&_msgBuffer);

            printf("[MessageDispatch] Player Exit. SerialNumber : %d\n", _exit.serialnumber());

            Server::BroadCast(_msgBuffer, (short)PacketID::Exit, _exit.ByteSizeLong());

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
            
            int serialNum = _move.serialnumber() - 1;

            _playerSlot[serialNum]._position._x = _move.x();
            _playerSlot[serialNum]._position._y = _move.y();
            _playerSlot[serialNum]._position._z = _move.z();
            _playerSlot[serialNum]._speed = _move.speed();

            //_syncPlayer.set_serialnumber(_playerSlot[serialNum]._serialNumber);
            //_syncPlayer.set_x(_playerSlot[serialNum]._position._x);
            //_syncPlayer.set_y(_playerSlot[serialNum]._position._y);
            //_syncPlayer.set_z(_playerSlot[serialNum]._position._z);

            //long byteSize = _syncPlayer.ByteSizeLong();

            //_syncPlayer.SerializeToString(&_msgBuffer);
            //Server::BroadCast(_msgBuffer, (short)PacketID::Sync, _syncPlayer.ByteSizeLong());

            break;
        } // case end
        case PacketID::StateChange:
        {
            _stateChange.ParseFromArray(packet._data, packet._packetSize - sizeof(PacketHeader));

            _playerSlot[_stateChange.serialnumber() - 1]._state = _stateChange.stateinfo();

            break;
        } // case end

        default:
            break;
        } // switch end
    } // while end
}
