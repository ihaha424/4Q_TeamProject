#include "pch.h"
#include "Application.h"

#include "DSHContentManager.h"
#include "DSHInputManager.h"
#include "DSHLoadManager.h"
#include "DSHTimeManager.h"
#include "DSHWindowManager.h"
#include "GEGraphicsManager.h"

Engine::Time::Manager* Engine::Application::_timeManager = nullptr;
Engine::Window::Manager* Engine::Application::_windowManager = nullptr;
Engine::GEGraphics::Manager* Engine::Application::_graphicsManager = nullptr;
Engine::Input::Manager* Engine::Application::_inputManager = nullptr;
Engine::Load::Manager* Engine::Application::_loadManager = nullptr;
Engine::Content::Manager* Engine::Application::_contentManager = nullptr;

Engine::Application::Application(const HINSTANCE instanceHandle, std::wstring title, const Math::Size size) :
	_instanceHandle(instanceHandle), _title(std::move(title)), _size(size)
{
}

void Engine::Application::Begin()
{
	// After
	CreateManagers();
	InitializeManagers();
	LoadGameData();
	DeclareInputActions(_inputManager);
	Register(_loadManager, _contentManager);

	//Before
	Setup({ _graphicsManager });
	InitializeContents();
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

void Engine::Application::Run(const int showCommand) const
{
	_windowManager->Show(showCommand);
	_windowManager->Update();
	_windowManager->SetCursorDefault();

	MSG message = {};
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
		{
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

			_drive.Update(deltaTime);
			// TODO: Alarm Timer for Fixed Update

			_graphicsManager->Render();
			_inputManager->Reset();
		}
	}
}

void Engine::Application::End()
{
	FinalizeContents();
	FinalizeManagers();
	DeleteManagers();
}

void Engine::Application::FinalizeContents()
{
	// TODO: WOC Manager Finalize;
	std::ranges::for_each(_worlds, [](World* world) { world->Finalize(); });
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

Engine::Load::IManager* Engine::Application::GetLoadManager()
{
	return _loadManager;
}

Engine::Content::IManager* Engine::Application::GetContentManager()
{
	static Content::Manager* contentManager = nullptr;
	CreateContentManager(&contentManager);
	return contentManager;
}

void Engine::Application::AddWorld(World* world)
{
	_worlds.push_back(world);
}

void Engine::Application::Attach(World* world)
{
	_drive.AttachWorld(world, nullptr);
}

void Engine::Application::CreateManagers()
{
	CreateTimeManager(&_timeManager);
	CreateWindowManager(&_windowManager);
	CreateInputManager(&_inputManager);
	CreateGraphicsManager(&_graphicsManager);
	CreateLoadManager(&_loadManager);
	CreateContentManager(&_contentManager);
}

void Engine::Application::InitializeManagers() const
{
	_timeManager->Initialize();
	_windowManager->Initialize(_instanceHandle, _title.c_str(), _size);
	_inputManager->Initialize(_windowManager->GetHandle());
	_graphicsManager->Initialize(_windowManager->GetHandle(), L"../Shaders/", _size, false, 1);
	_loadManager->Initialize();
}

void Engine::Application::LoadGameData()
{
	_loadManager->LoadGameData(_gameDataPath);

	auto configData = _loadManager->GetGameConfigData();

	// TODO: Get Data from ConfigData
	//if (const auto opTitle = configData.GetProperty<std::wstring>(L"Title"); opTitle.has_value()) _title = *opTitle;
	//if (const auto opSize = configData.GetProperty<Math::Size>(L"Size"); opSize.has_value()) _size = *opSize;
}

void Engine::Application::FinalizeManagers()
{
	_timeManager->Finalize();
	_windowManager->Finalize();
	_inputManager->Finalize();
	_graphicsManager->Finalize();
	_loadManager->Finalize();
	_contentManager->Finalize();
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
