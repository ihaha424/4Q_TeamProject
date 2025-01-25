#pragma once

namespace Engine::Network
{
    struct PacketFilter
    {
		template <typename T> /* requires std::is_base_of_v<Packet, T> */
		void operator()(Terminal* terminal, const T& packet) const
		{
			// TODO:: Implement packet filtering
		}
    };
}
