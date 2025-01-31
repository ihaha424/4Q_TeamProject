#pragma once

//struct Packet;

namespace Engine::Network
{
	// TODO: NetworkComponent base class
	class Terminal
	{
	public:
		Terminal() = default;
		Terminal(const Terminal& other) = default;
		Terminal(Terminal&& other) noexcept = default;
		Terminal& operator=(const Terminal& other) = default;
		Terminal& operator=(Terminal&& other) noexcept = default;
		virtual ~Terminal() = default;

		const int GetSerialNumber() const;
		void SetSerialNumber(int num);
		virtual void InvokeMessage(const Packet& packet) = 0;
	protected:
		int _serialNumber;

#ifndef CLIENT
	public:
		const unsigned long long GetSessionId() const;
		void SetSessionId(unsigned long long sid);
	protected :
		unsigned long long _sessionId;
#endif
	};
}
