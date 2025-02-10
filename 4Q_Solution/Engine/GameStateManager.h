#pragma once

namespace Engine::GameState
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		using Callback = std::function<void(const std::wstring&, const std::any&)>;
		using CallbackID = void*;

		/*****************************
				DataObserver
		 *****************************/
		virtual void RegisterData(const std::wstring& dataName, std::any data) = 0;

		virtual void SetData(const std::wstring& dataName, std::any newValue) = 0;
		virtual std::optional<std::any> GetData(const std::wstring& dataName) = 0;

		virtual void Subscribe(const std::wstring& dataName, Callback callback, CallbackID subscriber) = 0;
		virtual void Unsubscribe(const std::wstring& dataName, CallbackID id) = 0;


		/*****************************
				SubManager
		 *****************************/
		virtual void RegisterSubManager(const std::wstring& managerName, IManager* subManager) = 0;
		virtual void UnregisterSubManager(const std::wstring& managerName) = 0;
		virtual Engine::GameState::IManager* FindSubManager(const std::wstring& managerName) = 0;

		virtual Engine::GameState::IManager* NewSubManager() = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Finalize() = 0;
	};
}

