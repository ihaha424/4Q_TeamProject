#pragma once

namespace Engine::Network
{
	// TODO: NetworkComponent base class
	struct Terminal
	{
		Terminal() = default;
		Terminal(const Terminal& other) = default;
		Terminal(Terminal&& other) noexcept = default;
		Terminal& operator=(const Terminal& other) = default;
		Terminal& operator=(Terminal&& other) noexcept = default;
		virtual ~Terminal() = default;
	};
}
