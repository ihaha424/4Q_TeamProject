#include "pch.h"

// TODO: 서버에서 종료 패킷을 수신했을 때 내부 서버로직으로 해당 세션을 종료시키는 로직을 추가해야함
// TODO: 플레이어 오브젝트 추가.
// TODO: 움직임 동기화 제어
// TODO: 
// TODO: 
// TODO: 
// TODO: 

ServerLogic* _logic = nullptr;

int main()
{
    _logic = new ServerLogic();

    bool res = _logic->Initialize();
    if (res == false) {
        printf("[main] Server Initialize Failed. code : %d\n", GetLastError());
    }

    while (true) {
        _logic->Update();
    }
}
