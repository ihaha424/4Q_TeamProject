#include "pch.h"
#include "PacketFilter.h"

void Engine::Network::PacketFilter::operator()(Terminal* terminal, const Packet& packet) const
{
	// TODO:: Implement packet filtering
	if (packet._serialNumber == terminal->GetSerialNumber()) {
		terminal->InvokeMessage(packet);
	}
}
