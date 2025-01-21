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


        default:
            break;
        }
    }
}
