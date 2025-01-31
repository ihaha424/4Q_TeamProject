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
