#pragma once

namespace Engine::Graphics
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;
	};

	struct Manager : IManager
	{
		virtual void Initialize(HWND windowHandle, const std::filesystem::path& shaderRootPath, SIZE screenSize, bool isFullScreen, UINT animationThreadCount) = 0;
		virtual void PreUpdate(float deltaTime) const = 0;
		virtual void PostUpdate(float deltaTime) const = 0;
		virtual void Render() const = 0;
		virtual void Finalize() = 0;

		// Camera
		virtual void CreateCamera(Camera** camera) = 0;
		virtual void RegisterCamera(std::wstring_view name, Camera* camera) = 0;
		virtual void UnregisterCamera(std::wstring_view name) = 0;
		virtual void SetActiveCamera(std::wstring_view name) = 0;
	};
}
