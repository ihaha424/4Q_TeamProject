#include "ClientNetwork.h"
#include "Socket.h"
#include "Utils/StreamBuffer.h"
#include "PacketDispatcher.h"
#include <iostream>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

bool ClientNetwork::Initialize()
{
	//need ini config file
	/*
	* 
	*/
	printf("[Initialize] Client Config File Location : ./ClientConfig.ini\n");
	printf("[Initialize] Client Config Loading...\n\n");
	std::string serverIp;

	std::wstring configFilePath = L"./ClientConfig.ini";

	// 파일이 존재하지 않으면 기본 설정값으로 설정하고,
	// 설정 파일을 생성합니다.
	if (!PathFileExists(configFilePath.c_str())) {
		_serverPort = ServerPort;
		_bufferSize = BufferSize;

		WritePrivateProfileString(L"Server", L"ServerPort", std::to_wstring(_serverPort).c_str(), configFilePath.c_str());
		WritePrivateProfileString(L"Server", L"ServerIP", L"127.0.0.1", configFilePath.c_str());
		WritePrivateProfileString(L"System", L"BufferSize", std::to_wstring(_bufferSize).c_str(), configFilePath.c_str());
	}
	
	_serverPort = GetPrivateProfileInt(L"Server", L"ServerPort", 2147483647, configFilePath.c_str());
	printf("[Initialize] ServerPort Load. PortNum : %llu\n", _serverPort);

	_bufferSize = GetPrivateProfileInt(L"System", L"BufferSize", 2147483647, configFilePath.c_str());
	printf("[Initialize] BufferSize Load. BufferSize : %llu\n", _bufferSize);

	std::wstring ip(INET_ADDRSTRLEN, L'\0');
	GetPrivateProfileString(L"Server", L"ServerIP", L"127.0.0.1", ip.data(), INET_ADDRSTRLEN, configFilePath.c_str());
	serverIp.assign(ip.begin(), ip.end());
	printf("[Initialize] ServerIp Load. Server Ip : %s\n", serverIp.c_str());

	printf("\n[Initialize] Server Config Load Completed.\n");

	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0) {
		printf("[Initialize] WSAStartup Failed. Code : %d\n", GetLastError());
		return false;
	}
	printf("[Initialize] WSAStartup Success.\n");

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(_serverPort);
	if (inet_pton(AF_INET, serverIp.c_str(), &(_serverAddr.sin_addr)) != 1) {
		return false;
	}

	_server = new Socket();

	bool res = false;
	if (!_server->Open(IPPROTO_TCP)) {
		printf("[Initialize] Socket Open Failed. Code : %d\n", GetLastError());
		return false;
	}
	printf("[Initialize] Socket Open Success.\n");

	_recvData = new char[_bufferSize];
	_sendData = new char[_bufferSize];
	_saveRecvData = new StreamBuffer(_bufferSize);
	_packetDispatcherInstance = PacketDispatcher::GetInstance();

	return true;
}

bool ClientNetwork::ConnectToServer()
{
	if (!_server->Connect(_serverAddr)) {
		printf("[ConnectToServer] Server Connect Failed. Code : %d\n", GetLastError());
		return false;
	}
	printf("[ConnectToServer] Server Connect Success.\n");

	_packetDispatcherInstance->SessionCreated(0);

	_recvThread = std::thread(
		[&]() {
			while (true) {
				int res = RecvUpdate();
				if (res == -1) {
					break;
				}
			}
		});

	return true;
}

int ClientNetwork::RecvUpdate()
{
	int res = _server->Recv(_recvData);
	if (res < 0) {
		return res;
	}
	int write = _saveRecvData->Write(_recvData, res);
	_packetDispatcherInstance->SaveRecvPacket(_saveRecvData, 0);

	if (write < res) {
		_saveRecvData->Write(&_recvData[write], res - write);
	}

	memset(_recvData, 0, _bufferSize);

	return res;
	//_session->RecvUpdate();
}

int ClientNetwork::SendUpdate()
{
	SendQueue* msgs = _packetDispatcherInstance->GetSendMessageContainer(0);
	if ((*msgs).empty()) {
		bool res = _packetDispatcherInstance->SwapSendPacketContainer(0);
		if (res == false) {
			return true;
		}
	}

	while (!(*msgs).empty()) {
		Packet msg = (*msgs).front();
		(*msgs).pop();
		if (_sendDataSize + msg._packetSize > _bufferSize) {
			break;
		}
		memcpy(&_sendData[_sendDataSize], PtrCast(char*, &msg), msg._packetSize);
		_sendDataSize += msg._packetSize;
	}

	int res = _server->Send(_sendData, _sendDataSize);

	_sendDataSize -= res;
	//memset(_sendData, 0, BufferSize);

	return res;
	//_session->SendUpdate();
}

void ClientNetwork::WaitDisconnect()
{
	_recvThread.join();
}

void ClientNetwork::Finalize()
{
	shutdown(_server->GetSocket(), SD_RECEIVE);

	closesocket(_server->GetSocket());
	delete _server;

	delete[] _recvData;
	delete[] _sendData;
}
