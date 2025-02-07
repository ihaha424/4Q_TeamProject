#pragma once

namespace Engine::GameState
{
	struct IManager
	{
		using notifiy = std::function<void(void)>;

		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		virtual void RegisterSubManager(IManager* _subManager) = 0;
		virtual void AttachEvent(std::wstring _event, const notifiy& _callback) = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Finalize() = 0;
	};
}

