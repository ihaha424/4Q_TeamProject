#include <iostream>
#include "Server/ServerEntrance.h"
#include "PacketID.h"
#include "DSHTime/Time.h"

bool Initialize();
void Finalize();
void MessageDispatch();

PacketQueue* messageContainer = nullptr;

DSH::Time::ISystem* _system = nullptr;
DSH::Time::ITickTimer* _timer = nullptr;



// TODO: 서버에서 종료 패킷을 수신했을 때 내부 서버로직으로 해당 세션을 종료시키는 로직을 추가해야함
// TODO: 플레이어 오브젝트 추가.
// TODO: 움직임 동기화 제어
// TODO: 
// TODO: 
// TODO: 
// TODO: 

int main()
{
    bool res = true;
    res = Initialize();
    if (res == false) {
        printf("[main] Server Initialize Failed. Code : %d\n", GetLastError());
    }

    while (true) {
        _timer->Tick();

        MessageDispatch();

        // TODO: 내부적으로 업데이트 할 로직을 여기다 넣습니다.

        Server::SendUpdate();
    }

    Finalize();
}

bool Initialize() {
    bool res = true;
    res = Server::Initialize();
    if (res == false) {
        return false;
    }
    messageContainer = Server::GetPacketContainer();

    DSH::Time::CreateSystem()(&_system);
    _system->CreateTickTimer(&_timer);
    delete _system;

    return true;
}

void Finalize() {
    delete _timer;
}

void MessageDispatch() {
    if (messageContainer->empty()) {
        bool res = Server::SwapPacketContainer();
        if (res == false) {
            return;
        }
    }

    while (!messageContainer->empty()) {
        Packet packet = messageContainer->front();
        messageContainer->pop();

        switch ((PacketID)packet._packetId) {


        default:
            break;
        }
    }

}