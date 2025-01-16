#pragma once

namespace Engine::Manager::GraphicsSystem
{
	struct ICameraSystem
	{
		ICameraSystem() = default;
		ICameraSystem(const ICameraSystem& other) = default;
		ICameraSystem(ICameraSystem&& other) noexcept = default;
		ICameraSystem& operator=(const ICameraSystem& other) = default;
		ICameraSystem& operator=(ICameraSystem&& other) noexcept = default;
		virtual ~ICameraSystem() = default;

		virtual void CreateCamera(GE::ICamera** camera) const = 0;
		virtual void RegisterCamera(std::wstring_view name, GE::ICamera* camera) const = 0;
		virtual void Unregister(std::wstring_view name) const = 0;
		virtual void SetCurrentCamera(std::wstring_view name) const = 0;
	};

	class CameraSystem final : public ICameraSystem
	{
	public:
		CameraSystem() = default;

		void Initialize(GE::ICameraSystem* cameraSystem);
		void Update() const;
		void Finalize();

		void CreateCamera(GE::ICamera** camera) const override;
		void RegisterCamera(std::wstring_view name, GE::ICamera* camera) const override;
		void Unregister(std::wstring_view name) const override;
		void SetCurrentCamera(std::wstring_view name) const override;

	private:
		GE::ICameraSystem* _cameraSystem;
	};
}