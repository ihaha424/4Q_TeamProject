#pragma once

namespace Engine::Network
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		virtual void DispatchPacket() = 0;
		virtual void Register(Terminal* terminal) = 0;
		virtual void Unregister(Terminal* terminal) = 0;
		virtual void SaveSendData(short packetId, std::string& data, long dataSize, int serialNum) = 0;
		virtual void RegistWorldEvent(short packetId, std::function<void(int)> callback) = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize() = 0;
		virtual void Send() = 0;
		virtual void Receive() = 0;
		virtual void Finalize() = 0;
	};
}
