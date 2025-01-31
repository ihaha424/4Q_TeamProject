#include "NetworkMain.h"
#include "Socket.h"
#include "Session.h"
#include "PacketDispatcher.h"
#include <iostream>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

bool NetworkMain::Initialize()
{
	//need ini config file
	/*
	* 
	*/
	printf("[Initialize] Server Config File Location : ./ServerConfig.ini\n");
	printf("[Initialize] Server Config Loading...\n");
	//ULL serverPort, bufferSize, threadCount;

	std::wstring configFilePath = L"./ServerConfig.ini";

	// 파일이 존재하지 않으면 기본 설정값으로 설정하고,
	// 설정 파일을 생성합니다.
	if (!PathFileExists(configFilePath.c_str())) {
		_serverPort = ServerPort;
		_bufferSize = BufferSize;
		_threadCount = ThreadCount;

		WriteToIniFile(L"Server", L"ServerPort", std::to_wstring(_serverPort), configFilePath);
		WriteToIniFile(L"System", L"BufferSize", std::to_wstring(_bufferSize), configFilePath);
		WriteToIniFile(L"System", L"ThreadCount", std::to_wstring(_threadCount), configFilePath);
	}

	_serverPort = GetIntDataFromIniFile(L"Server", L"ServerPort", configFilePath);
	printf("[Initialize] ServerPort Load. PortNum : %llu\n", _serverPort);

	_bufferSize = GetIntDataFromIniFile(L"System", L"BufferSize", configFilePath);
	printf("[Initialize] BufferSize Load. BufferSize : %llu\n", _bufferSize);

	_threadCount = GetIntDataFromIniFile(L"System", L"ThreadCount", configFilePath);
	printf("[Initialize] ThreadCount Load. ThreadCount : %llu\n", _threadCount);

	printf("\n[Initialize] Server Config Load Completed.\n");


	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0) {
		return false;
	}
	printf("[Initialize] WSAStartup Success.\n");

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(_serverPort);
	_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	_listen = new Socket();

	bool res = false;
	if (!_listen->Open(IPPROTO_TCP)) {
		printf("[Initialize] Socket Open Failed. Code : %d\n", GetLastError());
		return false;
	}
	printf("[Initialize] Socket Open Success.\n");

	if (!_listen->Bind(_serverAddr)) {
		printf("[Initialize] Socket Bind Failed. Code : %d\n", GetLastError());
		return false;
	}
	printf("[Initialize] Socket Bind Success.\n");

	if (!_listen->Listen()) {
		printf("[Initialize] Socket Listen Failed. Code : %d\n", GetLastError());
		return false;
	}
	printf("[Initialize] Socket Listen Success.\n");


	for (int i = 0; i < 2; i++) {
		res = CreateWaitingSession();
		if (res == false) {
			printf("Make Pending Accept Session Failed. Code : %d\n", GetLastError());
			return false;
		}
	}

	printf("[Initialize] Make Pending Accept Session Success.\n");

	HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, _threadCount);
	if (completionPort == INVALID_HANDLE_VALUE) {
		printf("[Initialize] Completion Port Create Failed. Code : %d\n", GetLastError());
	}
	printf("[Initialize] Completion Port Create Success.\n");

	_cpContainer.push_back(completionPort);

	CreateIoCompletionPort((HANDLE)_listen->GetSocket(), completionPort, 0, 0);



	for (int i = 0; i < _threadCount; i++) {
		std::thread thread(&NetworkMain::IOWork, this, completionPort);
		thread.detach();
	}

	return true;
}

void NetworkMain::SendUpdate()
{
	HANDLE cp = _cpContainer[0];
	for (auto& [sid, session] : _sessionMap) {
		if (_sessionProcessCheck[sid] == false) {
			_sessionProcessCheck[sid] = true;
			PostQueuedCompletionStatus(cp, SEND, (ULONG_PTR)session, 0);
			//printf("[SendUpdate] sessionProcess Check false SessionID : %llu\n", session->GetSessionID());
		}
	}

	for (Session* session : _pendingDestroySessions) {
		Socket* socket = session->Release();
		printf("[IOWork] Session Released.\n");
		socket->Close();
		printf("[IOWork] Socket Closed.\n");
		delete session;
		delete socket;
	} // for end
	_pendingDestroySessions.clear();
}

void NetworkMain::Finalize()
{
	for (HANDLE cp : _cpContainer) {
		for (size_t i = 0; i < _threadCount; i++) {
			PostQueuedCompletionStatus(cp, DWMAX, 0, 0);
		}
	}
}

void NetworkMain::Disconnect(SessionID sid)
{
	// TODO: 여기서 session에 대한 종료를 진행해야 합니다.
	_pendingDestroySessions.push_back(_sessionMap[sid]);
	_sessionMap.erase(sid);
}

void NetworkMain::IOWork(HANDLE completionPort)
{
	DWORD byteTransferred;
	ULONG_PTR completionKey;
	OVERLAPPED* overlapped;
	while (true) {
		bool res = GetQueuedCompletionStatus(completionPort, &byteTransferred, &completionKey, &overlapped, INFINITE);
		if (res == false) {
			if (byteTransferred == 0) {
				Session* session = (Session*)completionKey;
				SessionID sid = session->GetSessionID();

				Lock lock(_sessionMtx);
				_pendingDestroySessions.push_back(session);
				_sessionMap.erase(sid);
				printf("[IOWork] Session deleted.\n");
			} // if end
		} // if end
		else {
			if (byteTransferred == DWMAX) {
				printf("[IOWork] IOThread Terminated\n");
				return;
			} // if end
			else if (byteTransferred == SEND) {
				Session* session = (Session*)completionKey;
				session->SendUpdate();

				_sessionProcessCheck[session->GetSessionID()] = false;
				//printf("[IOWork] sessionProcess Check true SessionID : %llu\n", session->GetSessionID());

			} // else if end
			else {
				OverlappedType* overlappedType = (OverlappedType*)overlapped;
				if (overlappedType->_overlappedType == OlType::Accept) {
					printf("[IOWork] New Client Accepted\n");

					AcceptOverlapped* acceptOverlapped = (AcceptOverlapped*)overlapped;

					Session* newSession = acceptOverlapped->_session;
					memcpy(newSession->_recvOl._buffer, acceptOverlapped->_buffer, acceptOverlapped->acceptBufferSize);
					newSession->_recvOl.InternalHigh = acceptOverlapped->InternalHigh;
					PacketDispatcher::GetInstance()->SessionCreated(newSession->GetSessionID());

					CreateIoCompletionPort((HANDLE)acceptOverlapped->_client->GetSocket(), completionPort, (ULONG_PTR)newSession, 0);
					printf("[IOWork] New Socket HANDLE connect to CompletionPort.\n");

					newSession->RecvUpdate();

					Lock lock(_sessionMtx);
					_sessionMap.insert({ newSession->GetSessionID(), newSession });
					_sessionProcessCheck.insert({ newSession->GetSessionID(), false });

					res = CreateWaitingSession();

					delete acceptOverlapped;
				}

				//printf("[IOWork] Packet Received\n");
				Session* session = (Session*)completionKey;
				if (overlappedType->_overlappedType == OlType::Recv) {
					session->RecvUpdate();
				} // if end
			} // if end
		} // else end
		

	}
}

bool NetworkMain::CreateWaitingSession()
{
	bool res = true;

	AcceptOverlapped* acceptOl = new AcceptOverlapped();
	acceptOl->_overlappedType = OlType::Accept;
	acceptOl->_listen = _listen->GetSocket();
	acceptOl->_client = new Socket();
	res = acceptOl->_client->Open(IPPROTO_TCP);
	if (res == false) {
		printf("[CreateWaitingSession] Socket Open Failed.\n");
		delete acceptOl->_client;
		delete acceptOl;
		return false;
	}

	acceptOl->_session = new Session();
	acceptOl->_session->Initialize(acceptOl->_client, _bufferSize);

	_listen->AcceptExtend(*acceptOl);
	printf("[CreateWaitingSession] Pending Accept Completed.\n");

	return true;
}

void NetworkMain::WriteToIniFile(const wchar_t* section, const wchar_t* key, std::wstring value, std::wstring& filePath)
{
	WritePrivateProfileString(section, key, value.c_str(), filePath.c_str());
}

int NetworkMain::GetIntDataFromIniFile(const wchar_t* section, const wchar_t* key, std::wstring& filePath, int defaultValue)
{
	return GetPrivateProfileInt(section, key, defaultValue, filePath.c_str());
}
