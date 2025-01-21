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

		void CreateCamera(Graphics::Camera** camera) override;
		void RegisterCamera(std::wstring_view name, Graphics::Camera* camera) override;

		void UnregisterCamera(std::wstring_view name) override;
		void SetActiveCamera(std::wstring_view name) override;

	private:
		HMODULE _dll;

		GE::IGraphicsSystem* _graphicsSystem;

		// Sub systems
		GE::IRenderSystem* _renderSystem;
		GE::ICameraSystem* _cameraSystem;
		GE::IAnimationSystem* _animationSystem;
		GE::ILightSystem* _lightSystem;
		GE::ITextSystem* _textSystem;
	};
}
