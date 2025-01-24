#pragma once

namespace Engine::GEGraphics
{
	class Manager final : public Graphics::Manager
	{
		using CreateInstanceFunction = HRESULT(__stdcall*)(void* ppv);
	public:
		Manager() = default;

		void Initialize(HWND windowHandle, const std::filesystem::path& shaderRootPath, SIZE screenSize,
			bool isFullScreen, UINT animationThreadCount) override;
		void Update(float deltaTime) const override;
		void Render() const override;
		void Finalize() override;

		// Camera
		void CreateCamera(Graphics::Camera** camera) override;
		void RegisterCamera(std::wstring_view name, Graphics::Camera* camera) override;
		void UnregisterCamera(std::wstring_view name) override;
		void SetActiveCamera(std::wstring_view name) override;

		GE::IRenderSystem* GetRenderSystem() const { return _renderSystem; }
		GE::ICameraSystem* GetCameraSystem() const  { return _cameraSystem; }
		GE::IAnimationSystem* GetAnimationSystem() const { return _animationSystem; }
		GE::ILightSystem* GetLightSystem() const  { return _lightSystem; }
		GE::ITextSystem* GetTextSystem() const  { return _textSystem; }
		GE::IPostProcessSystem* GetPostProcessSystem() const { return _postprocessSystem; }

	private:
		HMODULE _dll;

		GE::IGraphicsSystem* _graphicsSystem;

		// Sub systems
		GE::IRenderSystem* _renderSystem;
		GE::ICameraSystem* _cameraSystem;
		GE::IAnimationSystem* _animationSystem;
		GE::ILightSystem* _lightSystem;
		GE::ITextSystem* _textSystem;
		GE::IPostProcessSystem* _postprocessSystem;
		
	};
}
