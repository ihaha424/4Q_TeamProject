#include "pch.h"
#include "PacketFilter.h"

void Engine::Network::PacketFilter::operator()(Terminal* terminal, const Packet& packet) const
{
	// TODO:: Implement packet filtering
	if (packet._serialNumber == static_cast<Engine::Component::SynchronizeComponent*>(terminal)->GetSerialNumber()) {
		static_cast<Engine::Component::SynchronizeComponent*>(terminal)->InvokeMessage(packet);
	}
}
