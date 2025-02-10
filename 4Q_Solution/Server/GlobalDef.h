#ifndef _GLOBALDEF_
#define _GLOBALDEF_

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <mswsock.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#include <thread>
#include <mutex>
#include <string>
#include <memory>
#include <map>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <cassert>


// ============ DLL Setting ============
#include "DLLSetting.h"

// ============ Declaration ============
//struct Packet;

// ============ TypeSetting ============

using ULL = unsigned long long;
using SessionID = ULL;
using Lock = std::lock_guard<std::mutex>;



// ============ Macro ============

#define PtrCast(type, data) reinterpret_cast<type>(data)
#define PacketDataSize(packetSize) packetSize - sizeof(PacketHeader)

// ============ Const Data ============
// 초기 설정 값이 들어있습니다.

constexpr DWORD DWMAX = (std::numeric_limits<DWORD>::max)();
constexpr ULL ServerPort = 7777;
constexpr ULL BufferSize = 16384;
constexpr ULL ThreadCount = 2;

#endif