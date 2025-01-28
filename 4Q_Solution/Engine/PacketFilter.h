#pragma once

namespace Engine::Network
{
	class Terminal;

    struct PacketFilter
    {
        void operator()(Terminal* terminal, const Packet& packet) const;
    };
}
