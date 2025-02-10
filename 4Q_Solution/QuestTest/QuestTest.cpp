#include <iostream>
#include "../Engine/pch.h"
#include "../Engine/ServerNetworkManager.h"
#include <conio.h>

Engine::ServerNetwork::Manager* _serverManager = nullptr;
Engine::Component::Synchronize* _sync1 = nullptr; // Ray
Engine::Component::Synchronize* _sync2 = nullptr; // Live

std::string order;
int id;
int curDialogId;

int curQuestId1;
int curQuestId2;
int curPuzzle = 0;

struct TestObject {
    void Initialize(int num) {
        _sync = new Engine::Component::Synchronize();
        _serverManager->Register(_sync);
        _sync->SetSerialNumber(num);

        _sync->AddCallback((short)PacketID::QuestClear, &TestObject::QuestClear, this);
        _sync->AddCallback((short)PacketID::QuestStart, &TestObject::QuestStart, this);
        _sync->AddCallback((short)PacketID::PlayDialog, &TestObject::DialogPlay, this);
    }

    void QuestClear(const PlayMsg::QuestEnd* msg) {
        printf("Quest Clear. Quest ID : %d\n", msg->questid());
    }
    void QuestStart(const PlayMsg::QuestStart* msg) {
        printf("Quest Start. Quest ID : %d\n", msg->questid());
        curQuestId = msg->questid();
    }
    void DialogPlay(const PlayMsg::DialogProgress* msg) {
        printf("Dialog Start. Dialog ID : %d\n", msg->nextdialogid());
        curDialogId = msg->nextdialogid();
    }
    void PuzzleStart(const PlayMsg::PuzzleStart* msg) {
        printf("Puzzle Start. Puzzle Num : %d\n", msg->puzzleid());
    }
    void PuzzleProcess(const PlayMsg::ObjectActive* msg) {
        printf("Object Actived. Object ID : %d\n", msg->objectserialnumber());
    }
    void InteractDialog() {
        if (curDialogId == -1) {
            printf("No Dialog Playing.\n");
            return;
        }
        _sync->_interactDialog.set_currentdialogid(curDialogId);
        _sync->_interactDialog.SerializeToString(&_sync->_msgBuffer);
        _serverManager->SaveSendData((short)PacketID::InteraceDialog, _sync->_msgBuffer, _sync->_interactDialog.ByteSizeLong(), _sync->GetSerialNumber());
    }
    void InteractObject(int id) {
        _sync->_interactObject.set_objectserialnumber(id);
        _sync->_interactObject.SerializeToString(&_sync->_msgBuffer);
        _serverManager->SaveSendData((short)PacketID::InteractObject, _sync->_msgBuffer, _sync->_interactObject.ByteSizeLong(), _sync->GetSerialNumber());
    }

    int curDialogId;
    int curQuestId;
    Engine::Component::Synchronize* _sync = nullptr;
};

std::atomic<bool> end = false;
TestObject* _obj1 = nullptr;
TestObject* _obj2 = nullptr;
std::string objectName;

int main()
{
    _serverManager = new Engine::ServerNetwork::Manager();
    _serverManager->Initialize();
    _obj1 = new TestObject();
    _obj2 = new TestObject();
    _obj1->Initialize(1);
    _obj2->Initialize(2);

    while (true) {
        _serverManager->DispatchPacket();

        if (_kbhit()) { // 키 입력 감지
            char key = _getch();
            if (key == '\r') {
                printf("Enter Order.\n");
                std::cin >> order;
                if (order == "interact") {
                    std::cin >> objectName;
                    std::cin >> id;
                    if (objectName == "ray") {
                        _obj1->InteractObject(id);
                    }
                    else if (objectName == "live") {
                        _obj2->InteractObject(id);
                    }
                }
                else if (order == "dialognext") {
                    std::cin >> objectName;
                    if (objectName == "ray") {
                        _obj1->InteractDialog();
                    }
                    else if (objectName == "live") {
                        _obj2->InteractDialog();
                    }
                }
                else if (order == "curpuzzle") {
                    printf("CurPuzzle : %d\n", curPuzzle);
                }
            }
        }


        _serverManager->Send();
    }
    end = true;
    _serverManager->Disconnect();
    _serverManager->Finalize();

}


