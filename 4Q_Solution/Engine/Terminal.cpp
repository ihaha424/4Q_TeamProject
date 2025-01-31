#include "pch.h"
#include "Terminal.h"

const int Engine::Network::Terminal::GetSerialNumber() const
{
    return _serialNumber;
}

void Engine::Network::Terminal::SetSerialNumber(int num)
{
    _serialNumber = num;
}

#ifndef CLIENT
const unsigned long long Engine::Network::Terminal::GetSessionId() const
{
    return _sessionId;
}

void Engine::Network::Terminal::SetSessionId(unsigned long long sid)
{
    _sessionId = sid;
}
#endif