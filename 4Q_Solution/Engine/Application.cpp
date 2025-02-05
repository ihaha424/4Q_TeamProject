#include "pch.h"
#include "Application.h"

#include "DSHContentManager.h"
#include "DSHInputManager.h"
#include "DSHLoadManager.h"
#include "DSHLoggerManager.h"
#include "DSHTimeManager.h"
#include "DSHWindowManager.h"
#include "GEGraphicsManager.h"
#include "ServerNetworkManager.h"
#include "PHIManager.h"

Engine::Time::Manager* Engine::Application::_timeManager = nullptr;
Engine::Window::Manager* Engine::Application::_windowManager = nullptr;
Engine::GEGraphics::Manager* Engine::Application::_graphicsManager = nullptr;
Engine::Input::Manager* Engine::Application::_inputManager = nullptr;
Engine::Load::Manager* Engine::Application::_loadManager = nullptr;
Engine::Content::Manager* Engine::Application::_contentManager = nullptr;
Engine::Network::Manager* Engine::Application::_networkManager = nullptr;
Engine::Physics::Manager* Engine::Application::_physicsManager = nullptr;
Engine::Logger::Manager* Engine::Application::_loggerManager = nullptr;

Engine::Application::Application(const HINSTANCE instanceHandle):
	_instanceHandle(instanceHandle), _size(Math::Size::Zero)
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
			
			_contentManager->Contraction(Modules{ 
				.graphicsManager = _graphicsManager,
				.physicsManager = _physicsManager,
                .loadManager = _loadManager
			});
			_networkManager->DispatchPacket();

		    _physicsManager->Update(deltaTime);
		    _physicsManager->FetchScene(true);
		
			_contentManager->Update(deltaTime);

			while (_timeManager->IsFixedUpdate())
			{
				_contentManager->FixedUpdate();
			}

			_contentManager->Relaxation();

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

void Engine::Application::Register(Content::IManager* contentManager, Load::IManager* loadManager)
{
	const auto componentFactory = contentManager->GetComponentFactory();
	componentFactory->Register<Component::Movement>();
	componentFactory->Register<Component::Light>();
	componentFactory->Register<Component::StaticMesh>();
	componentFactory->Register<Component::Camera>(1.f, 1000.f, _size, std::numbers::pi_v<float> / 4);
	componentFactory->Register<Component::TextRenderer>();
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
    CreateContentManager(&_contentManager);	
    CreateNetworkManager(&_networkManager);
    CreatePhysicsManager(&_physicsManager);
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
	_contentManager->Initialize();
    _networkManager->Initialize();
    _physicsManager->Initialize(Engine::Physics::PhysicsType::Physx, false);
}

void Engine::Application::LoadGameData()
{
	_loadManager->Initialize();
	LoadData(_loadManager);

	const auto configData = _loadManager->GetGameConfigData();
	_title = configData.GetProperty<std::wstring>(L"Title").value_or(L"Game");
	_size = configData.GetProperty<Math::Size>(L"Size").value_or(Math::Size{ 1920, 1080 });
}

void Engine::Application::FinalizeManagers()
{
	_contentManager->Finalize();
	_loadManager->Finalize();
	_graphicsManager->Finalize();
	_inputManager->Finalize();
	_windowManager->Finalize();
    _timeManager->Finalize();
    _networkManager->Finalize();
    _physicsManager->Finalize();
	_loggerManager->Finalize();
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
    deleter(&_networkManager);
    deleter(&_physicsManager);
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
