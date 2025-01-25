#pragma once

namespace Engine::Network {
	class Terminal;
	struct PacketFilter;
}


namespace Engine::ServerNetwork {
	using TerminalList = std::list<Engine::Network::Terminal*>;

	class Manager final : public Engine::Network::Manager
	{
	public:
		Manager();

		void Initialize() override;
		void Send() override;
		void Receive() override;
		void Finalize() override;

		void Register(Engine::Network::Terminal* terminal) override;
		void Unregister(Engine::Network::Terminal* terminal) override;

		void DispatchPacket();
		void SaveSendData(short packetId, std::string& data, long dataSize) override;
	private:
		TerminalList _terminalList;
		PacketQueue* _msgContainer = nullptr;
		Engine::Network::PacketFilter _filter;

	};

}

