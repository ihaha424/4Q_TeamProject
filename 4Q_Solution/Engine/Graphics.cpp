#include "pch.h"
#include "Graphics.h"

void Engine::Manager::Graphics::Initialize(const HWND windowHandle, const std::filesystem::path& shaderRootPath, 
	const SIZE screenSize,	const bool isFullScreen, const UINT animationThreadCount)
{
	constexpr Utility::ThrowIfFailed thrower;

	const wchar_t* path = nullptr;

#ifdef _DEBUG
	SetDllDirectory(L"../dll/Debug");
	path = L"GraphicsEngine_d.dll";
#else
	SetDllDirectory(L"../dll/Release");
	path = L"GraphicsEngine.dll";
#endif

	thrower(LoadLibrary(path), &_dll);

	const CreateInstanceFunction pCreateFunc = reinterpret_cast<CreateInstanceFunction>(GetProcAddress(_dll, "DllCreateInstance"));
	thrower(pCreateFunc(&_graphicsSystem));

	// CameraSystem
	GE::ICameraSystem* cameraSystem = nullptr;
	_graphicsSystem->CreateCameraSystem(&cameraSystem);
	_cameraSystem.Initialize(cameraSystem);


	// RenderSystem
	GE::IRenderSystem* renderSystem = nullptr;
	_graphicsSystem->CreateRenderSystem(&renderSystem);
	const GE::RENDERER_DESC desc
	{
		.hWnd = windowHandle,
		.shaderRootPath = shaderRootPath.c_str(),
		.width = static_cast<float>(screenSize.cx),
		.height = static_cast<float>(screenSize.cy),
		.type = GE::RENDERER_DESC::Type::DX11,
		.isFullScreen = isFullScreen
	};
	_renderSystem.Initialize(renderSystem, &desc);

	// AnimationSystem
	GE::IAnimationSystem* animationSystem = nullptr;
	_graphicsSystem->CreateAnimationSystem(&animationSystem);
	_animationSystem.Initialize(animationSystem, animationThreadCount);

	// LightSystem
	GE::ILightSystem* lightSystem = nullptr;
	_graphicsSystem->CreateLightSystem(&lightSystem);
	_lightSystem.Initialize(lightSystem);
}

void Engine::Manager::Graphics::Update(const float deltaTime) const
{
	_animationSystem.Update(deltaTime);
	_cameraSystem.Update();
}

void Engine::Manager::Graphics::Render() const
{
	_renderSystem.Render();
}

void Engine::Manager::Graphics::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	_lightSystem.Finalize();
	_animationSystem.Finalize();
	_cameraSystem.Finalize();
	_renderSystem.Finalize();
	releaser(&_graphicsSystem);

	FreeLibrary(_dll);
}

Engine::Manager::GraphicsSystem::ICameraSystem* Engine::Manager::Graphics::GetCameraSystem()
{
	return &_cameraSystem;
}

Engine::Manager::GraphicsSystem::IRenderSystem* Engine::Manager::Graphics::GetRenderSystem()
{
	return &_renderSystem;
}

Engine::Manager::GraphicsSystem::IAnimationSystem* Engine::Manager::Graphics::GetAnimationSystem()
{
	return &_animationSystem;
}

Engine::Manager::GraphicsSystem::ILightSystem* Engine::Manager::Graphics::GetLightSystem()
{
	return &_lightSystem;
}