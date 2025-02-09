#pragma once

namespace Engine::UGameState
{
	class Manager final : public Engine::GameState::Manager
	{
	public:
		Manager();

		/*****************************
				DataObserver
		 *****************************/
		void RegisterData(const std::wstring& dataName, std::any data) override;

		void SetData(const std::wstring& dataName, std::any newValue) override;
		std::optional<std::any> GetData(const std::wstring& dataName) override;

		void Subscribe(const std::wstring& dataName, Callback callback, CallbackID subscriber) override;
		void Unsubscribe(const std::wstring& dataName, CallbackID id) override;


		/*****************************
				SubManager
		 *****************************/
		void RegisterSubManager(const std::wstring& managerName, IManager* subManager) override;
		void UnregisterSubManager(const std::wstring& managerName) override;
		Engine::GameState::IManager* FindSubManager(const std::wstring& managerName) override;

		Engine::GameState::IManager* NewSubManager() override;


		/*****************************
				Engine
		 *****************************/
		void Initialize() override;
		void Update(float deltaTime) override;
		void Finalize() override;


	private:
		void NotifySubscribers(const std::wstring& stateName);

	private:

		/*****************************
				DataObserver
		 *****************************/
		std::unordered_map<std::wstring, std::any> datas;
		std::unordered_map<std::wstring, std::vector<std::pair<CallbackID, Callback>>> subscribers;
	

		/*****************************
				SubManager
		 *****************************/
		std::unordered_map<std::wstring, Engine::GameState::IManager*> subManagers;
	};
}

