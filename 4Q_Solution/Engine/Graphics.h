#pragma once
#include "GraphicsSystems.h"

namespace Engine::Manager
{
	struct IGraphics
	{
		IGraphics() = default;
		IGraphics(const IGraphics& other) = default;
		IGraphics(IGraphics&& other) noexcept = default;
		IGraphics& operator=(const IGraphics& other) = default;
		IGraphics& operator=(IGraphics&& other) noexcept = default;
		virtual ~IGraphics() = default;

		[[nodiscard]] virtual GraphicsSystem::ICameraSystem* GetCameraSystem() = 0;
		[[nodiscard]] virtual GraphicsSystem::IRenderSystem* GetRenderSystem() = 0;
		[[nodiscard]] virtual GraphicsSystem::IAnimationSystem* GetAnimationSystem() = 0;
		[[nodiscard]] virtual GraphicsSystem::ILightSystem* GetLightSystem() = 0;
	};

	class Graphics final : public IGraphics
	{
		using CreateInstanceFunction = HRESULT(__stdcall*)(void* ppv);
	public:
		Graphics() = default;

		void Initialize(HWND windowHandle, const std::filesystem::path& shaderRootPath, SIZE screenSize, bool isFullScreen, UINT animationThreadCount);
		void Update(float deltaTime) const;
		void Render() const;
		void Finalize();

		[[nodiscard]] GraphicsSystem::ICameraSystem* GetCameraSystem() override;
		[[nodiscard]] GraphicsSystem::IRenderSystem* GetRenderSystem() override;
		[[nodiscard]] GraphicsSystem::IAnimationSystem* GetAnimationSystem() override;
		[[nodiscard]] GraphicsSystem::ILightSystem* GetLightSystem() override;

	private:
		HMODULE _dll;

		GE::IGraphicsSystem* _graphicsSystem;

		// Sub systems
		GraphicsSystem::RenderSystem _renderSystem;
		GraphicsSystem::CameraSystem _cameraSystem;
		GraphicsSystem::AnimationSystem _animationSystem;
		GraphicsSystem::LightSystem _lightSystem;
	};
}


//// �׽�Ʈ�� GameObject
//struct GameObject
//{
//	GE::IMeshRenderer* pComponent;
//	GE::IMatrix* pMatrix;
//	GE::IAnimator* pAnimator;
//};
//
//// �׽�Ʈ�� ObjectManager
//#include <vector>
//#include <list>
//std::vector<GameObject> g_components;
//std::list<GE::ILight*> g_lights;

//void Engine::Application::SetupGraphicsEngineTutorial()
//{
//	auto CreateMeshAndMatrix = [](const wchar_t* filePath, GE::MESH_RENDERER_DESC::Type type) -> GameObject
//		{
//			GE::IMeshRenderer* pComponent = nullptr;
//			GE::IMatrix* pMatrix = nullptr;
//
//			GE::MESH_RENDERER_DESC meshDesc
//			{
//				.filePath = filePath,
//				.type = type
//			};
//
//			_renderSystem->CreateMeshRenderer(&pComponent, &meshDesc);
//			_renderSystem->CreateMatrix(&pMatrix);
//
//			return { pComponent, pMatrix, nullptr };
//		};
//
//	// InitializeStaticMeshRenderer
//	GE::MATRIX_DESC matDesc{};
//	auto components = CreateMeshAndMatrix(L"../Resources/FBX/char.fbx", GE::MESH_RENDERER_DESC::Type::Static);
//	components.pMatrix->CreateScaleMatrix(&matDesc, 1.f, 1.f, 1.f);
//	components.pMatrix->SetDesc(&matDesc);
//	g_components.emplace_back(components);
//
//	/*components = CreateMeshAndMatrix(L"../Resources/cerberusT.fbx", GE::MESH_RENDERER_DESC::Type::Static);
//	components.pMatrix->CreateScaleMatrix(&matDesc, 1.f, 1.f, 1.f);
//	components.pMatrix->SetDesc(&matDesc);
//	g_components.emplace_back(components);*/
//
//	// InitializeSkeletaMeshRenderer	
//	components = CreateMeshAndMatrix(L"../Resources/Player/Player.X", GE::MESH_RENDERER_DESC::Type::Skeletal);
//	components.pMatrix->CreateScaleMatrix(&matDesc, 1.f, 1.f, 1.f);
//
//	GE::MATRIX_DESC matTranslate{};
//	components.pMatrix->CreateTranslateMatrix(&matTranslate, 0.f, 0.f, -100.f);
//	components.pMatrix->Multiply(&matDesc, &matTranslate, &matDesc);
//	components.pMatrix->SetDesc(&matDesc);
//	g_components.emplace_back(components);
//
//	_animationSystem->RegisterAnimator(components.pComponent, &components.pAnimator);
//	components.pAnimator->ChangeAnimation("Run");
//	
//	for (auto& [component, matrix, animaotr] : g_components)
//	{
//		_renderSystem->RegisterRenderQueue(component, matrix);
//	}
//
//	// InitializeMultiLight
//	GE::ILight* pLight = nullptr;	
//	/*_lightSystem->RegisterLight(&pLight);
//	pLight->SetType(GE::ILight::Type::Point);
//	pLight->SetPosition(0.f, 20.f, 0.f);
//	pLight->SetRange(200.f);
//	pLight->SetIntensity(1.f);
//	g_lights.push_back(pLight);*/
//
//	_lightSystem->RegisterLight(&pLight);
//	pLight->SetType(GE::ILight::Type::Directional);
//	pLight->SetDirection(0.f, 0.f, 1.f);
//	pLight->SetIntensity(1.f);
//	g_lights.push_back(pLight);
//

	//// InitializeCamera
	//GE::ICamera* pCamera = nullptr;
	//_cameraSystem->CreateCamera(L"MainCamera", &pCamera);
	//_cameraSystem->SetCurrentCamera(L"MainCamera");
	//pCamera->SetPerspective(1.f, 1000.f, (float)_size.cx / (float)_size.cy, 3.141592f / 4);
	//pCamera->SetPosition(0.f, 50.f, -300.f);


//
//	// GE FinalizeContents;
//	for (auto& [component, matrix, animator] : g_components)
//	{
//		component->Release();
//		matrix->Release();
//		if (animator) animator->Release();
//	}
//
//	for (auto& light : g_lights)
//		light->Release();
//}
