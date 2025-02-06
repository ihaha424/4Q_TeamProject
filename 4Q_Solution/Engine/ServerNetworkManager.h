#pragma once

namespace Engine::Network {
	class Terminal;
	struct PacketFilter;
}


namespace Engine::ServerNetwork {
	using TerminalList = std::list<Engine::Network::Terminal*>;
	using WorldCallback = std::unordered_map<short, std::function<void(const ConnectMsg::AddObject*)>>;

	class Manager final : public Engine::Network::Manager
	{
	public:
		Manager();

		void Initialize() override;
		void Send() override;
		void Receive() override;
		void Finalize() override;
		void Disconnect() override;

		void Register(Engine::Network::Terminal* terminal) override;
		void Unregister(Engine::Network::Terminal* terminal) override;

		void DispatchPacket() override;
		void SaveSendData(short packetId, std::string data, long dataSize, int serialNum) override;
		void RegistWorldEvent(short packetId, std::function<void(const ConnectMsg::AddObject*)> callback) override;
	private:
		TerminalList _terminalList;
		PacketQueue* _msgContainer = nullptr;
		Engine::Network::PacketFilter _filter;

		WorldCallback _worldCallback;
		ConnectMsg::AddObject _addObject;
	};

}

