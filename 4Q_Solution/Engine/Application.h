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
		Application(HINSTANCE instanceHandle, std::wstring title, SIZE size);


		void Begin();
		void Run(int showCommand);
		void End();

		static Time::IManager* GetTimeManager();
		static Input::IManager* GetInputManager();
		static Graphics::IManager* GetGraphicsManager();

	protected:
		void AddWorld(World* world); // TODO: Remove this.
		void Attach(World* world);

		void InitializeManagers() const;
		virtual void DeclareInputActions(Input::IManager* inputManager);
		virtual void Addition(); // TODO: Remove this.
		void Setup(Modules modules);
		virtual void InitializeContents();
		virtual void FinalizeContents();
		void FinalizeManagers() const;

		HINSTANCE _instanceHandle;

	private:
		static void CreateTimeManager(Time::Manager** timeManager);
		static void CreateWindowManager(Manager::Window** windowManager);
		static void CreateInputManager(Input::Manager** inputManager);
		static void CreateGraphicsManager(GEGraphics::Manager** graphicsManager);

		static Time::Manager* _timeManager;
		static Manager::Window* _windowManager;
		static Input::Manager* _inputManager;
		static GEGraphics::Manager* _graphicsManager;

		std::wstring _title;
		SIZE _size;

		Drive _drive;

		std::vector<World*> _worlds; // TODO: Remove this.
	};
}

