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

	_graphicsSystem->CreateRenderSystem(&_renderSystem);
	_graphicsSystem->CreateCameraSystem(&_cameraSystem);

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
	_renderSystem->GetTextSystem(&_textSystem);

	_graphicsSystem->CreateAnimationSystem(&_animationSystem);
	_animationSystem->Initialize(animationThreadCount);

	_graphicsSystem->CreateLightSystem(&_lightSystem);
}

void Engine::Manager::Graphics::Update(const float deltaTime) const
{
	_animationSystem->Update(deltaTime);
	_cameraSystem->Update();
}

void Engine::Manager::Graphics::Render() const
{
	_renderSystem->Render();
}

void Engine::Manager::Graphics::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	releaser(&_animationSystem);
	releaser(&_cameraSystem);
	releaser(&_renderSystem);
	releaser(&_lightSystem);
	releaser(&_graphicsSystem);

	FreeLibrary(_dll);
}

void Engine::Manager::Graphics::CreateCamera(GE::ICamera** camera) const
{
	_cameraSystem->CreateCamera(camera);
}

void Engine::Manager::Graphics::RegisterCamera(const std::wstring_view name, GE::ICamera* camera) const
{
	_cameraSystem->RegisterCamera(name.data(), camera);
}

void Engine::Manager::Graphics::Unregister(const std::wstring_view name) const
{
	_cameraSystem->UnRegisterCamera(name.data());
}

void Engine::Manager::Graphics::SetCurrentCamera(const std::wstring_view name) const
{
	_cameraSystem->SetCurrentCamera(name.data());
}

void Engine::Manager::Graphics::CreateMatrix(GE::IMatrix** matrix) const
{
	_renderSystem->CreateMatrix(matrix);
}

void Engine::Manager::Graphics::CreateMeshRenderer(GE::IMeshRenderer** component, const GE::MESH_RENDERER_DESC* desc) const
{
	_renderSystem->CreateMeshRenderer(component, desc);
}

void Engine::Manager::Graphics::RegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* component, GE::IMatrix* matrix) const
{
	_renderSystem->RegisterRenderQueue(layer, component, matrix);
}

void Engine::Manager::Graphics::UnRegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* component) const
{
	_renderSystem->UnRegisterRenderQueue(layer, component);
}

void Engine::Manager::Graphics::CreateAnimator(GE::IMeshRenderer* meshRenderer, GE::IAnimator** outAnimator) const
{
	_animationSystem->CreateAnimator(meshRenderer, outAnimator);
}

void Engine::Manager::Graphics::RegisterAnimator(GE::IAnimator* animator) const
{
	_animationSystem->RegisterAnimator(animator);
}

void Engine::Manager::Graphics::UnRegisterAnimator(GE::IAnimator* animator) const
{
	_animationSystem->UnRegisterAnimator(animator);
}

void Engine::Manager::Graphics::CreateLight(GE::ILight** outLight) const
{
	_lightSystem->CreateLight(outLight);
}

void Engine::Manager::Graphics::RegisterLight(GE::ILight* light) const
{
	_lightSystem->RegisterLight(light);
}

void Engine::Manager::Graphics::UnRegisterLight(GE::ILight* light) const
{
	_lightSystem->UnRegisterLight(light);
}

void Engine::Manager::Graphics::RegisterFont(const wchar_t* name, const wchar_t* filePath) const
{
	_textSystem->RegisterFont(name, filePath);
}

void Engine::Manager::Graphics::CreateTextRenderer(GE::ITextRenderer** textRenderer) const
{
	_textSystem->CreateTextRenderer(textRenderer);
}

void Engine::Manager::Graphics::RegisterRenderQueue(GE::ITextRenderer* textRenderer) const
{
	_textSystem->RegisterRenderQueue(textRenderer);
}

void Engine::Manager::Graphics::UnRegisterRenderQueue(GE::ITextRenderer* textRenderer) const
{
	_textSystem->UnRegisterRenderQueue(textRenderer);
}
