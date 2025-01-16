#pragma once

namespace Engine
{
	class Application
	{
	public:
		Application(HINSTANCE instanceHandle, std::wstring title, SIZE size);


		void Begin();
		void Run(int showCommand);
		void End();

		static Manager::ITime* GetTimeManager();
		static Input::IManager* GetInputManager();
		static Manager::IGraphics* GetGraphicsManager();

	protected:
		void InitializeManagers() const;
		virtual void DeclareInputActions(Input::IManager* inputManager);
		void CreateContents();
		void InitializeContents();
		void FinalizeContents();
		void DeleteContents();
		void FinalizeManagers() const;

		HINSTANCE _instanceHandle;

	private:
		static void CreateTimeManager(Manager::Time** timeManager);
		static void CreateWindowManager(Manager::Window** windowManager);
		static void CreateInputManager(Input::Manager** inputManager);
		static void CreateGraphicsManager(Manager::Graphics** graphicsManager);

		static Manager::Time* _timeManager;
		static Manager::Window* _windowManager;
		static Input::Manager* _inputManager;
		static Manager::Graphics* _graphicsManager;

		std::wstring _title;
		SIZE _size;

		Drive _drive;

		Component::CameraComponent* _cameraComponent; // TODO: Remove this.
	};
}

