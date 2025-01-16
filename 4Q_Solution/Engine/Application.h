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
		static Manager::IInput* GetInputManager();
		static Manager::IGraphics* GetGraphicsManager();

	protected:
		void InitializeManagers() const;
		virtual void DeclareInputActions(Manager::IInput* inputManager);
		void CreateContents();
		void InitializeContents();
		void FinalizeContents();
		void DeleteContents();
		void FinalizeManagers() const;

		HINSTANCE _instanceHandle;

	private:
		static void CreateTimeManager(Manager::Time** timeManager);
		static void CreateWindowManager(Manager::Window** windowManager);
		static void CreateInputManager(Manager::Input** inputManager);
		static void CreateGraphicsManager(Manager::Graphics** graphicsManager);

		static Manager::Time* _timeManager;
		static Manager::Window* _windowManager;
		static Manager::Input* _inputManager;
		static Manager::Graphics* _graphicsManager;

		std::wstring _title;
		SIZE _size;

		Drive _drive;

		Component::CameraComponent* _cameraComponent; // TODO: Remove this.
	};
}

