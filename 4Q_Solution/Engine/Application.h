#pragma once

namespace Engine::GEGraphics
{
	class Manager;
}

namespace Engine::ServerNetwork 
{
	class Manager;
}

namespace Engine::Physics
{
	class Manager;
}

namespace Engine
{
	class Application
	{
	public:
		Application(HINSTANCE instanceHandle, std::wstring title, SIZE size);
		virtual ~Application() = default;


		void Begin();
		void Run(int showCommand);
		void End();

		static Time::IManager* GetTimeManager();
		static Input::IManager* GetInputManager();
		static Graphics::IManager* GetGraphicsManager();
		static Network::IManager* GetNetworkManager();
		static Physics::IManager* GetPhysicsManager();

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
		static void CreateWindowManager(Window::Manager** windowManager);
		static void CreateInputManager(Input::Manager** inputManager);
		static void CreateGraphicsManager(GEGraphics::Manager** graphicsManager);
		static void CreateNetworkManager(ServerNetwork::Manager** networkManager);
		static void CreatePhysicsManager(Physics::Manager** physicsManager);

		static Time::Manager* _timeManager;
		static Window::Manager* _windowManager;
		static Input::Manager* _inputManager;
		static GEGraphics::Manager* _graphicsManager;
		static ServerNetwork::Manager* _networkManager;
		static Physics::Manager* _physicsManager;

		std::wstring _title;
		SIZE _size;

		Drive _drive;

		std::vector<World*> _worlds; // TODO: Remove this.
	};
}

