#include "pch.h"
#include "Application.h"

#include "DSHInputManager.h"
#include "DSHTimeManager.h"
#include "DSHWindowManager.h"
#include "GEGraphicsManager.h"
#include "ServerNetworkManager.h"
#include "PHIManager.h"

Engine::Time::Manager* Engine::Application::_timeManager = nullptr;
Engine::Window::Manager* Engine::Application::_windowManager = nullptr;
Engine::GEGraphics::Manager* Engine::Application::_graphicsManager = nullptr;
Engine::Input::Manager* Engine::Application::_inputManager = nullptr;
Engine::ServerNetwork::Manager* Engine::Application::_networkManager = nullptr;
Engine::Physics::Manager* Engine::Application::_physicsManager = nullptr;

Engine::Application::Application(const HINSTANCE instanceHandle, std::wstring title, const SIZE size) :
	_instanceHandle(instanceHandle),
	_title(std::move(title)),
	_size(size)
{
}

void Engine::Application::Begin()
{
	InitializeManagers();
	DeclareInputActions(_inputManager);
	Addition(); // TODO: Refactor this.
	Setup({ _graphicsManager, _physicsManager });
	InitializeContents();
}

void Engine::Application::InitializeManagers() const
{
	CreateTimeManager(&_timeManager);
	_timeManager->Initialize();

	CreateWindowManager(&_windowManager);
	_windowManager->Initialize(_instanceHandle, _title.c_str(), _size);

	CreateInputManager(&_inputManager);
	_inputManager->Initialize(_windowManager->GetHandle());

	CreateGraphicsManager(&_graphicsManager);
	_graphicsManager->Initialize(_windowManager->GetHandle(), L"../Shaders/", _size, false, 1);

	CreateNetworkManager(&_networkManager);
	_networkManager->Initialize();

	CreatePhysicsManager(&_physicsManager);
	_physicsManager->Initialize();
}

void Engine::Application::DeclareInputActions(Input::IManager* inputManager)
{
}

void Engine::Application::Addition()
{
}

void Engine::Application::Setup(Modules modules)
{
	std::ranges::for_each(_worlds, [modules](World* world) { world->Setup(modules); });
}


void Engine::Application::InitializeContents()
{
	// TODO: WOC Manager Initialize;
	std::ranges::for_each(_worlds, [](World* world) { world->Initialize(); });
}

void Engine::Application::Run(const int showCommand)
{
	_windowManager->Show(showCommand);
	_windowManager->Update();
	_windowManager->SetCursorDefault();

	MSG message = {};
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
		{
			// TODO: check DestroyMessage and Send to Server
			// TODO: if receive DestroyOk then end.
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			const float metaTime = _timeManager->GetDeltaMetaTime();
			const float deltaTime = _timeManager->GetDeltaTime();

			_timeManager->Tick();
			_inputManager->Update(metaTime);
			_graphicsManager->Update(deltaTime);
			// _networkManager->DispatchPacket();
			_physicsManager->Update(metaTime);
			_physicsManager->FetchSecne(true);
			_drive.Update(deltaTime);
			// TODO: Alarm Timer for Fixed Update

			_graphicsManager->Render();
			_inputManager->Reset();
			_networkManager->Send();
		}
	}
}

void Engine::Application::End()
{
	FinalizeContents();
	FinalizeManagers();
}

void Engine::Application::FinalizeContents()
{
	// TODO: WOC Manager Finalize;
	std::ranges::for_each(_worlds, [](World* world) { world->Finalize(); });
}

void Engine::Application::FinalizeManagers() const
{
	constexpr Utility::SafeDelete deleter;

	_graphicsManager->Finalize();
	deleter(&_graphicsManager);
	_inputManager->Finalize();
	deleter(&_inputManager);
	_windowManager->Finalize();
	deleter(&_windowManager);
	_timeManager->Finalize();
	deleter(&_timeManager);
	//_networkManager->Finalize();
	//deleter(&_networkManager);
	_physicsManager->Finalize();
	deleter(&_physicsManager);
}

Engine::Time::IManager* Engine::Application::GetTimeManager()
{
	return _timeManager;
}

Engine::Input::IManager* Engine::Application::GetInputManager()
{
	return _inputManager;
}

Engine::Graphics::IManager* Engine::Application::GetGraphicsManager()
{
	return _graphicsManager;
}

Engine::Network::IManager* Engine::Application::GetNetworkManager()
{
	return _networkManager;
}

Engine::Physics::IManager* Engine::Application::GetPhysicsManager()
{
	return _physicsManager;
}

void Engine::Application::AddWorld(World* world)
{
	_worlds.push_back(world);
}

void Engine::Application::Attach(World* world)
{
	_drive.AttachWorld(world, nullptr);
}

void Engine::Application::CreateTimeManager(Time::Manager** timeManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (timeManager == nullptr)	thrower(E_INVALIDARG);
	else
	{
		Time::Manager* manager = new DSHTime::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		if (timeManager != nullptr) *timeManager = manager;
	}
}

void Engine::Application::CreateWindowManager(Window::Manager** windowManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (windowManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		Window::Manager* manager = new DSHWindow::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*windowManager = manager;
	}
}

void Engine::Application::CreateInputManager(Input::Manager** inputManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (inputManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		Input::Manager* manager = new DSHInput::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*inputManager = manager;
	}
}

void Engine::Application::CreateGraphicsManager(GEGraphics::Manager** graphicsManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (graphicsManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		GEGraphics::Manager* manager = new GEGraphics::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*graphicsManager = manager;
	}
}

void Engine::Application::CreateNetworkManager(ServerNetwork::Manager** networkManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (networkManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		ServerNetwork::Manager* manager = new ServerNetwork::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*networkManager = manager;
	}
}

void Engine::Application::CreatePhysicsManager(Physics::Manager** physicsManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (physicsManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		Physics::Manager* manager = new PHI::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*physicsManager = manager;
	}
}
