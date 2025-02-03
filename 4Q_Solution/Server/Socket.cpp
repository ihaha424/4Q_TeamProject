#include "pch.h"
#include "Socket.h"

bool Socket::Open(int protocol)
{
	if (protocol == IPPROTO_TCP) {
		_socket = WSASocket(AF_INET, SOCK_STREAM, protocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
		if (_socket == INVALID_SOCKET) {
			return false;
		}
	}

	return true;
}

bool Socket::Bind(SOCKADDR_IN& addr)
{
	int res = bind(_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (res == SOCKET_ERROR) {
		return false;
	}

	return true;
}

bool Socket::Listen()
{
	int res = listen(_socket, SOMAXCONN);
	if (res == SOCKET_ERROR) {
		return false;
	}

	return true;
}

void Socket::Close()
{
	closesocket(_socket);
}

bool Socket::Connect(SOCKADDR_IN& addr)
{
	int res = WSAConnect(_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN), 0, 0, 0, 0);
	if (res == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			return false;
		}
	}

	return true;
}

SOCKET Socket::Accept()
{
	SOCKADDR_IN clientAddr;
	int len = sizeof(clientAddr);
	SOCKET client = accept(_socket, (SOCKADDR*)&clientAddr, &len);
	if (client == INVALID_SOCKET) {
		int error = WSAGetLastError();
		if (error == WSAENOTSOCK || error == WSAEINTR) {
			return INVALID_SOCKET;
		}
	}

	return client;
}

bool Socket::AcceptExtend(AcceptOverlapped& overlapped)
{
	int res = AcceptEx(
		overlapped._listen,
		overlapped._client->GetSocket(),
		overlapped._buffer,
		overlapped.acceptBufferSize,
		AddressLength,
		AddressLength,
		&overlapped._recvByte,
		&overlapped
	);

	if (res == SOCKET_ERROR) {
		if (res != WSA_IO_PENDING) {
			return false;
		}
	}

	return true;
}

bool Socket::Recv(RecvOverlapped& overlapped)
{
	_recv.buf = overlapped._buffer;
	_recv.len = overlapped._bufferSize;

	DWORD flg = 0;

	int res = WSARecv(
		overlapped._listen,
		&_recv,
		1,
		&overlapped._byteRecv,
		&flg,
		&overlapped,
		NULL
	);
	if (res == SOCKET_ERROR) {
		if (GetLastError() != WSA_IO_PENDING) {
			return false;
		}
	}

	return true;
}

bool Socket::Send(SendOverlapped& overlapped)
{
	_send.buf = overlapped._buffer;
	_send.len = overlapped._dataSize;

	int res = WSASend(
		_socket,
		&_send,
		1,
		&overlapped._byteSend,
		0,
		&overlapped,
		NULL
	);

	if (res < 0) {
		if (GetLastError() != WSA_IO_PENDING) {
			return false;
		}
	}

	overlapped._dataSize -= overlapped.InternalHigh;
	overlapped._byteSend -= overlapped.InternalHigh;
	memset(overlapped._buffer, 0, BufferSize);

	return true;
}

int Socket::Recv(char* buffer)
{
	_recv.buf = buffer;
	_recv.len = BufferSize;

	DWORD byteRecv;
	DWORD flg = 0;

	int res = WSARecv(
		_socket, 
		&_recv, 
		1, 
		&byteRecv, 
		&flg, 
		nullptr, 
		nullptr
	);

	if (res < 0) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			return -1;
		}
	}

	return byteRecv;
}

int Socket::Send(char* buffer, int len)
{
	_send.buf = buffer;
	_send.len = len;

	DWORD byteSend;

	int res = WSASend(
		_socket,
		&_send,
		1,
		&byteSend,
		0,
		nullptr,
		nullptr
	);

	if (res < 0) {
		if (GetLastError() != WSAEWOULDBLOCK) {
			return false;
		}
	}

	return byteSend;
}
