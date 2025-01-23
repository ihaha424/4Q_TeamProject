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
		Application(HINSTANCE instanceHandle, std::wstring title, Math::Size size);
		virtual ~Application() = default;


		void Begin();
		void Run(int showCommand) const;
		void End();

	protected:
		void AddWorld(World* world); // TODO: Remove this.
		void Attach(World* world);

		virtual void DeclareInputActions(Input::IManager* inputManager);
		virtual void Addition(); // TODO: Remove this.
		void Setup(Modules modules);
		virtual void InitializeContents();
		virtual void FinalizeContents();

	private:
		static void CreateManagers();
		void InitializeManagers() const;
		void LoadGameData();

		static void FinalizeManagers();
		static void DeleteManagers();

		HINSTANCE _instanceHandle;

		std::filesystem::path _gameDataPath; // TODO: Setup from constructor.

		// TODO: Setup from file.
		std::wstring _title;
		Math::Size _size;

		Drive _drive;
		std::vector<World*> _worlds; // TODO: Remove this.

	public:
		static Time::IManager* GetTimeManager();
		static Input::IManager* GetInputManager();
		static Graphics::IManager* GetGraphicsManager();
		static Load::IManager* GetLoadManager();

	private:
		static void CreateTimeManager(Time::Manager** timeManager);
		static void CreateWindowManager(Window::Manager** windowManager);
		static void CreateInputManager(Input::Manager** inputManager);
		static void CreateGraphicsManager(GEGraphics::Manager** graphicsManager);
		static void CreateLoadManager(Load::Manager** loadManager);

		static Time::Manager* _timeManager;
		static Window::Manager* _windowManager;
		static Input::Manager* _inputManager;
		static GEGraphics::Manager* _graphicsManager;
		static Load::Manager* _loadManager;
	};
}

