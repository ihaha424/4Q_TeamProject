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

		virtual void Register()
	};

	struct Manager : IManager
	{
		virtual void Initialize() = 0;
		virtual void Send() = 0;
		virtual void Receive() = 0;
		virtual void Finalize() = 0;
	};
}
