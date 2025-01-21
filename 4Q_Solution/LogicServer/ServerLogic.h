#pragma once
#include "Server/ServerEntrance.h"
#include "PacketID.h"
#include "DSHTime/Time.h"

class ServerLogic
{
public:
	ServerLogic() = default;
	~ServerLogic() = default;

	bool Initialize();
	void Update();
	void Finalize();


private:
	DSH::Time::ISystem* _system = nullptr;
	DSH::Time::ITickTimer* _timer = nullptr;

	PacketQueue* _messageContainer = nullptr;

	void MessageDispatch();
};

