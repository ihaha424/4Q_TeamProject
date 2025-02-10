#pragma once

namespace Engine::GEGraphics
{
	class Manager;
}

namespace Engine
{
	class Application
	{
	public:
		explicit Application(HINSTANCE instanceHandle);
		Application(const Application& other) = default;
		Application(Application&& other) noexcept = default;
		Application& operator=(const Application& other) = default;
		Application& operator=(Application&& other) noexcept = default;
		virtual ~Application() = default;


		void Begin();
		void Run(int showCommand);
		void End();

	protected:
		virtual void LoadData(Load::IManager* loadManager) = 0;
		virtual void DeclareInputActions(Input::IManager* inputManager) = 0;
		virtual void Register(Content::IManager* contentManager, Load::IManager* loadManager);
		virtual void PrepareInitialWorld(Content::Factory::World* worldFactory) = 0;

	private:
		static void CreateManagers();
		void InitializeManagers() const;
		void LoadGameData();

		static void FinalizeManagers();
		static void DeleteManagers();

		HINSTANCE _instanceHandle;

		std::filesystem::path _gameDataPath;

		// TODO: Setup from file.
		std::wstring _title;
		Math::Size _size;

	public:
		static Time::IManager* GetTimeManager();
		static Input::IManager* GetInputManager();
		static Graphics::IManager* GetGraphicsManager();
	    static Network::IManager* GetNetworkManager();
	    static Physics::IManager* GetPhysicsManager();
	    static Load::IManager* GetLoadManager();
		static Content::IManager* GetContentManager();
		static Logger::IManager* GetLoggerManager();
		static GameState::IManager* GetGameStateManager();
		static Audio::IManager* GetSoundManager();

	private:
		static void CreateTimeManager(Time::Manager** timeManager);
		static void CreateWindowManager(Window::Manager** windowManager);
		static void CreateInputManager(Input::Manager** inputManager);
		static void CreateGraphicsManager(GEGraphics::Manager** graphicsManager);
	    static void CreateNetworkManager(Network::Manager** networkManager);
	    static void CreatePhysicsManager(Physics::Manager** physicsManager);
	    static void CreateLoadManager(Load::Manager** loadManager);
		static void CreateContentManager(Content::Manager** contentManager);
		static void CreateLoggerManager(Logger::Manager** loggerManager);
		static void CreateGameStateManager(GameState::Manager** gameStateManager);
		static void CreateSoundManager(DSHAudio::Manager** soundManager);

		static Time::Manager* _timeManager;
		static Window::Manager* _windowManager;
		static Input::Manager* _inputManager;
		static GEGraphics::Manager* _graphicsManager;
	    static Network::Manager* _networkManager;
	    static Physics::Manager* _physicsManager;
	    static Load::Manager* _loadManager;
		static Content::Manager* _contentManager;
		static Logger::Manager* _loggerManager;
		static GameState::Manager* _gameStateManager;
		static DSHAudio::Manager* _soundManager;
	};
}

