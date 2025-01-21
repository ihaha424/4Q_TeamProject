#include "pch.h"
#include "GEGraphicsManager.h"

#include "GEGraphicsCamera.h"

void Engine::GEGraphics::Manager::Initialize(HWND windowHandle, const std::filesystem::path& shaderRootPath,
                                             SIZE screenSize, bool isFullScreen, UINT animationThreadCount)
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
	_graphicsSystem->CreateCameraSystem(&_cameraSystem);

	// RenderSystem
	_graphicsSystem->CreateRenderSystem(&_renderSystem);
	const GE::RENDERER_DESC desc
	{
		.hWnd = windowHandle,
		.shaderRootPath = shaderRootPath.c_str(),
		.width = static_cast<float>(screenSize.cx),
		.height = static_cast<float>(screenSize.cy),
		.type = GE::RENDERER_DESC::Type::DX11,
		.maxLayer = 1,
		.isFullScreen = isFullScreen
	};
	_renderSystem->Initialize(&desc);

	// TextSystem
	_renderSystem->GetTextSystem(&_textSystem);

	// AnimationSystem
	_graphicsSystem->CreateAnimationSystem(&_animationSystem);
	_animationSystem->Initialize(animationThreadCount);

	// LightSystem
	_graphicsSystem->CreateLightSystem(&_lightSystem);
}

void Engine::GEGraphics::Manager::Update(const float deltaTime) const
{
	_animationSystem->Update(deltaTime);
	_cameraSystem->Update();
}

void Engine::GEGraphics::Manager::Render() const
{
	_renderSystem->Render();
}

void Engine::GEGraphics::Manager::Finalize()
{
	constexpr Utility::SafeRelease releaser;
	releaser(&_lightSystem);
	releaser(&_animationSystem);
	releaser(&_renderSystem);
	releaser(&_cameraSystem);
	releaser(&_graphicsSystem);
	FreeLibrary(_dll);
}

void Engine::GEGraphics::Manager::CreateCamera(Graphics::Camera** camera)
{
	if (camera == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	GE::ICamera* geCamera = nullptr;
	_cameraSystem->CreateCamera(&geCamera);
	Camera* temp = new Camera();
	if (temp == nullptr)
	{
		geCamera->Release();
		Utility::ThrowIfFailed()(E_OUTOFMEMORY);
	}
	temp->Setup(geCamera);
	*camera = temp;
}

void Engine::GEGraphics::Manager::RegisterCamera(const std::wstring_view name, Graphics::Camera* camera)
{
	const Camera* geCamera = static_cast<Camera*>(camera);
	_cameraSystem->RegisterCamera(name.data(), geCamera->Get());
}

void Engine::GEGraphics::Manager::UnregisterCamera(const std::wstring_view name)
{
	_cameraSystem->UnRegisterCamera(name.data());
}

void Engine::GEGraphics::Manager::SetActiveCamera(const std::wstring_view name)
{
	_cameraSystem->SetCurrentCamera(name.data());
}
