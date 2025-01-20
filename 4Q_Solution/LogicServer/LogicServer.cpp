#include <iostream>
#include "Server/ServerEntrance.h"

bool Initialize();

PacketQueue* messageContainer = nullptr;

// TODO: 서버에서 종료 패킷을 수신했을 때 내부 서버로직으로 해당 세션을 종료시키는 로직을 추가해야함.


int main()
{
    bool res = true;
    res = Initialize();
    if (res == false) {
        printf("[main] Server Initialize Failed. Code : %d\n", GetLastError());
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