#pragma once

namespace Engine
{
	class Application
	{
	public:
		Application(HINSTANCE instanceHandle, std::wstring title, SIZE size);

		void InitializeManagers() const;
		void CreateContents();
		void InitializeContents();
		void Run(int showCommand);
		void FinalizeContents();
		void DeleteContents();
		void FinalizeManagers() const;

		static Manager::Time* GetTimeManager();
		static Manager::Window* GetWindowManager();
		static Manager::Input* GetInputManager();
		static Manager::Graphics* GetGraphicsManager();

	protected:

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

