#include "pch.h"
#include "ThrowIfFailed.h"

#include <sstream>

std::string Engine::Utility::HResultToString::operator()(const HRESULT result) const
{
    char* tempMessage = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        result,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&tempMessage),
        0,
        nullptr
    );
    std::string message;
    if (tempMessage) {
        message = tempMessage;
        LocalFree(tempMessage);
    }
    else {
        std::ostringstream oss;
        oss << "Unknown HRESULT: 0x" << std::hex << result;
        message = oss.str();
    }
    return message;
}

std::string Engine::Utility::LastErrorToString::operator()(const DWORD error) const
{
    char* tempMessage = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&tempMessage),
        0,
        nullptr
    );
    std::string message;
    if (tempMessage) {
        message = tempMessage;
        LocalFree(tempMessage);
    }
    else {
        std::ostringstream oss;
        oss << "Unknown ERROR: 0x" << std::hex << error;
        message = oss.str();
    }
    return message;
}

void Engine::Utility::ThrowIfFailed::operator()(const HRESULT result) const
{
    if (result != S_OK) throw std::exception(HResultToString()(result).c_str());
}

void Engine::Utility::ThrowIfFailed::operator()(const HANDLE result, const LPHANDLE pHandle) const
{
	if (result == INVALID_HANDLE_VALUE) throw std::exception(LastErrorToString()(GetLastError()).c_str());
	*pHandle = result;
}

void Engine::Utility::ThrowIfFailed::operator()(const HINSTANCE result, HINSTANCE* pInstance) const
{
	if (result == nullptr) throw std::exception(LastErrorToString()(GetLastError()).c_str());
	*pInstance = result;
}
