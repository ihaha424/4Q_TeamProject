#include "pch.h"
#include "Application.h"

#include "DSHContentManager.h"
#include "DSHInputManager.h"
#include "DSHLoadManager.h"
#include "DSHLoggerManager.h"
#include "DSHAudioManager.h"
#include "DSHHudManager.h"
#include "DSHTimeManager.h"
#include "DSHWindowManager.h"
#include "GEGraphicsManager.h"
#include "ServerNetworkManager.h"
#include "PHIManager.h"
#include "UGameStateManager.h"

Engine::Time::Manager* Engine::Application::_timeManager = nullptr;
Engine::Window::Manager* Engine::Application::_windowManager = nullptr;
Engine::GEGraphics::Manager* Engine::Application::_graphicsManager = nullptr;
Engine::Input::Manager* Engine::Application::_inputManager = nullptr;
Engine::Load::Manager* Engine::Application::_loadManager = nullptr;
Engine::Content::Manager* Engine::Application::_contentManager = nullptr;
Engine::Network::Manager* Engine::Application::_networkManager = nullptr;
Engine::Physics::Manager* Engine::Application::_physicsManager = nullptr;
Engine::Logger::Manager* Engine::Application::_loggerManager = nullptr;
Engine::GameState::Manager* Engine::Application::_gameStateManager = nullptr;
Engine::DSHAudio::Manager* Engine::Application::_soundManager = nullptr;
Engine::DSHHud::Manager* Engine::Application::_hudManager = nullptr;

Engine::Math::Size Engine::Application::_size = Math::Size::Zero;

Engine::Application::Application(const HINSTANCE instanceHandle) :
	_instanceHandle(instanceHandle)
{
}

void Engine::Application::Begin()
{
	// After
	CreateManagers();
	LoadGameData();
	InitializeManagers();
	DeclareInputActions(_inputManager);
	Register(_contentManager, _loadManager);
	PrepareInitialHUD(_hudManager);
	PrepareInitialWorld(_contentManager->GetWorldFactory());
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
			_graphicsManager->PreUpdate(deltaTime);

			_hudManager->Contraction(Modules{
				.graphicsManager = _graphicsManager,
				.physicsManager = _physicsManager,
				.loadManager = _loadManager,
				.gameStateManager = _gameStateManager,
				.audioManager = _soundManager
				});

			_contentManager->Contraction(Modules{
				.graphicsManager = _graphicsManager,
				.physicsManager = _physicsManager,
				.loadManager = _loadManager,
				.gameStateManager = _gameStateManager,
				.audioManager = _soundManager
				});
			_networkManager->DispatchPacket();

			_physicsManager->Update(deltaTime);
			_physicsManager->FetchScene(true);

			while (_timeManager->IsFixedUpdate())
			{
				_hudManager->FixedUpdate();
				_contentManager->FixedUpdate();
			}

			_hudManager->Update(deltaTime);
			_contentManager->Update(deltaTime);
			_contentManager->LazyUpdate(deltaTime);

			_hudManager->Relaxation();
			_contentManager->Relaxation();

			_soundManager->Update();

			_graphicsManager->PostUpdate(deltaTime);
			_graphicsManager->Render();

			_inputManager->Reset();

			_networkManager->Send();

			_loggerManager->Flush();
		}
	}
	_networkManager->Disconnect();
}

void Engine::Application::End()
{
	FinalizeManagers();
	DeleteManagers();
}

Engine::Math::Size Engine::Application::GetSize()
{
	return _size;
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

Engine::Load::IManager* Engine::Application::GetLoadManager()
{
	return _loadManager;
}

Engine::Content::IManager* Engine::Application::GetContentManager()
{
	return _contentManager;
}

Engine::Logger::IManager* Engine::Application::GetLoggerManager()
{
	return _loggerManager;
}

Engine::GameState::IManager* Engine::Application::GetGameStateManager()
{
	return _gameStateManager;
}

Engine::Audio::IManager* Engine::Application::GetSoundManager()
{
	return _soundManager;
}

Engine::DSHHud::Manager* Engine::Application::GetHudManager()
{
	return _hudManager;
}

void Engine::Application::Register(Content::IManager* contentManager, Load::IManager* loadManager)
{
	const auto componentFactory = contentManager->GetComponentFactory();
	componentFactory->Register<Component::Movement>();
	componentFactory->Register<Component::Light>();
	componentFactory->Register<Component::StaticMesh>();
	componentFactory->Register<Component::Camera>(1.f, 5000.f, _size, std::numbers::pi_v<float> / 4);
	componentFactory->Register<Component::ShadowCamera>(500.f, 20000.f, _size, std::numbers::pi_v<float> / 4);
	componentFactory->Register<Component::Text>();
	componentFactory->Register<Component::SkeletalMesh>();
	componentFactory->Register<Component::Animator>();
	componentFactory->Register<Component::SkyBox>();
	componentFactory->Register<Component::RigidStatic>();
	componentFactory->Register<Component::RigidDynamic>();
	componentFactory->Register<Component::RigidKinematic>();
	componentFactory->Register<Component::Rigid>();
	componentFactory->Register<Component::ChractorController>();
	componentFactory->Register<Component::Synchronize>();
	componentFactory->Register<Component::FixedArm>();
	componentFactory->Register<Component::BitFlag>();
	componentFactory->Register<Component::EffectSound>();
	componentFactory->Register<Component::Effect3DSound>();
	componentFactory->Register<Component::BackgroundMusic>();
	componentFactory->Register<Component::Listener>();
	componentFactory->Register<Component::Sprite>();
	componentFactory->Register<Component::LineWave>();
	// TODO: Register other components.
}

void Engine::Application::CreateManagers()
{
	CreateLoggerManager(&_loggerManager);
	CreateTimeManager(&_timeManager);
	CreateWindowManager(&_windowManager);
	CreateInputManager(&_inputManager);
	CreateGraphicsManager(&_graphicsManager);
	CreateLoadManager(&_loadManager);
	CreateHudManager(&_hudManager);
	CreateContentManager(&_contentManager);
	CreateNetworkManager(&_networkManager);
	CreatePhysicsManager(&_physicsManager);
	CreateGameStateManager(&_gameStateManager);
	CreateSoundManager(&_soundManager);
}

void Engine::Application::InitializeManagers() const
{
	_loggerManager->Initialize(L"Dump.dmp");
	_loggerManager->EnableConsole();
	_timeManager->Initialize(0.2f);
	_windowManager->Initialize(_instanceHandle, _title.c_str(), _size);
	_inputManager->Initialize(_windowManager->GetHandle());
	_windowManager->AddProcedure(DSHInput::Manager::Procedure);
	_graphicsManager->Initialize(_windowManager->GetHandle(), L"../Shaders/", _size, false, 1);
	_hudManager->Initialize();
	_contentManager->Initialize();
    _networkManager->Initialize();
    //_physicsManager->Initialize(Engine::Physics::PhysicsType::Physx, true);
    _physicsManager->Initialize(Engine::Physics::PhysicsType::Physx, false);
	_gameStateManager->Initialize();
	_soundManager->Initialize();
}

void Engine::Application::LoadGameData()
{
	_loadManager->Initialize();
	LoadData(_loadManager);

	const auto configData = _loadManager->GetGameConfigData();
	_title = configData.GetProperty<std::wstring>(L"Title").value_or(L"Game");
	_size = configData.GetProperty<Math::Size>(L"Size").value_or(Math::Size{ 1600, 900 });
}

void Engine::Application::FinalizeManagers()
{
	_soundManager->Finalize();
	_contentManager->Finalize();
	_hudManager->Finalize();
	_loadManager->Finalize();
	_graphicsManager->Finalize();
	_inputManager->Finalize();
	_windowManager->Finalize();
	_timeManager->Finalize();
	_networkManager->Finalize();
	_physicsManager->Finalize();
	_loggerManager->Finalize();
	_gameStateManager->Finalize();
}

void Engine::Application::DeleteManagers()
{
	constexpr Utility::SafeDelete deleter;
	deleter(&_timeManager);
	deleter(&_windowManager);
	deleter(&_inputManager);
	deleter(&_graphicsManager);
	deleter(&_loadManager);
	deleter(&_contentManager);
	deleter(&_hudManager);
	deleter(&_networkManager);
	deleter(&_physicsManager);
	deleter(&_loggerManager);
	deleter(&_gameStateManager);
	deleter(&_soundManager);
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

void Engine::Application::CreateNetworkManager(Network::Manager** networkManager)
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

void Engine::Application::CreateLoadManager(Load::Manager** loadManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (loadManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		Load::Manager* manager = new DSHLoad::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*loadManager = manager;
	}
}

void Engine::Application::CreateContentManager(Content::Manager** contentManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (contentManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		Content::Manager* manager = new DSHContent::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*contentManager = manager;
	}
}

void Engine::Application::CreateLoggerManager(Logger::Manager** loggerManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (loggerManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		Logger::Manager* manager = new DSHLogger::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*loggerManager = manager;
	}
}

void Engine::Application::CreateGameStateManager(GameState::Manager** gameStateManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (gameStateManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		GameState::Manager* manager = new UGameState::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*gameStateManager = manager;
	}
}

void Engine::Application::CreateSoundManager(DSHAudio::Manager** soundManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (soundManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		DSHAudio::Manager* manager = new DSHAudio::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*soundManager = manager;
	}
}

void Engine::Application::CreateHudManager(DSHHud::Manager** hudManager)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (hudManager == nullptr) thrower(E_INVALIDARG);
	else
	{
		DSHHud::Manager* manager = new DSHHud::Manager();
		if (manager == nullptr) thrower(E_OUTOFMEMORY);
		*hudManager = manager;
	}
}
