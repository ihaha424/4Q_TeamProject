#include <iostream>
#include "Server/ServerEntrance.h"
#include "PacketID.h"

bool Initialize();
void MessageDispatch();

PacketQueue* messageContainer = nullptr;

// TODO: 서버에서 종료 패킷을 수신했을 때 내부 서버로직으로 해당 세션을 종료시키는 로직을 추가해야함.


int main()
{
    bool res = true;
    res = Initialize();
    if (res == false) {
        printf("[main] Server Initialize Failed. Code : %d\n", GetLastError());
    }

    while (true) {
        MessageDispatch();

        // TODO: 내부적으로 업데이트 할 로직을 여기다 넣습니다.

        Server::SendUpdate();
    }

}

bool Initialize() {
    bool res = true;
    res = Server::Initialize();
    if (res == false) {
        return false;
    }
    messageContainer = Server::GetPacketContainer();

    return true;
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