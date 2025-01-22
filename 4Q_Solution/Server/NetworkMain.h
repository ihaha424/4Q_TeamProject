#pragma once
#include "GlobalDef.h"
#include "Overlapped.h"


class Socket;
class Session;
class PacketDispatcher;

using CompletionPortContainer = std::vector<HANDLE>;
using SessionMap = std::unordered_map<SessionID, Session*>;
using AcceptOverlappedContainer = std::vector<AcceptOverlapped>;
using SendProcessing = std::map<SessionID, bool>;

#define SEND DWMAX - 1

class NetworkMain
{
public:
	NetworkMain() = default;
	~NetworkMain() = default;

	bool Initialize();
	void SendUpdate();
	void Finalize();
	void Disconnect(SessionID sid);

private:
	CompletionPortContainer _cpContainer;
	SessionMap _sessionMap;
	SOCKADDR_IN _serverAddr;
	Socket* _listen = nullptr;
	Socket* _client1 = nullptr;
	Socket* _client2 = nullptr;
	
	AcceptOverlapped _acceptOverlapped1;
	AcceptOverlapped _acceptOverlapped2;

	SendProcessing _sessionProcessCheck;

	ULL _bufferSize = 0;
	ULL _threadCount = 0;
	ULL _serverPort = 0;

	std::mutex _sessionMtx;

	void IOWork(HANDLE completionPort);
	bool CreateWaitingSession();

	void WriteToIniFile(const wchar_t* section, const wchar_t* key, std::wstring value, std::wstring& filePath);
	int GetIntDataFromIniFile(const wchar_t* section, const wchar_t* key, std::wstring& filePath, int defaultValue = (std::numeric_limits<int>::max)());
};

