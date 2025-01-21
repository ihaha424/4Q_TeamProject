# Server.DLL 사용 설명서

#include “ClientEntrance.h”를 사용하면 됩니다.

## bool Initialize()

- 서버와 연결하기 위해 내부 네트워크를 초기화 하는 과정입니다.
    
    초기화에 실패하면 GetLastError() 함수를 통해 오류를 조회하면 됩니다.
    

## bool ConnectToServer()

- 서버와 연결을 시도합니다. 성공하면 내부에서 데이터를 받는 스레드가 생성됩니다.
    
    실패하면 GetLastError() 함수를 통해 오류를 조회하면 됩니다.
    

## PacketQueue* GetPacketContainer()

- 서버에서 받은 메시지를 담고 있는 컨테이너를 반환합니다.

## bool SwapPacketContainer()

- 외부에서 사용할 컨테이너와 내부에서 사용하는 컨테이너를 스위칭하는 함수입니다.
    
    GetPacketContainer()를 통해 가져온 컨테이너가 비어있을 시 사용하면 됩니다.
    
    함수의 반환값이 false면 두 컨테이너 모두 비어있다는 뜻입니다.
    

## void SavePacketData(std::string msg, short packetId, long dataSize)

- SerializedAsString()함수를 통해 직렬화된 protobuf 메시지와 패킷 타입의 식별Id, 데이터 사이즈를 입력해주면 됩니다.
    
    내부에서 자동으로 패킷정보에 합쳐 전송하게 됩니다.
    

## void SendUpdate()

- 이 함수를 호출하면 내부에서 서버에 보낼 데이터들을 보냅니다.

## void Finalize()

- 이 함수를 사용하면 내부 네트워크 프로세스를 정리합니다.