#pragma once

namespace Engine::Manager::GraphicsSystem
{
	struct ILightSystem
	{
		ILightSystem() = default;
		ILightSystem(const ILightSystem& other) = default;
		ILightSystem(ILightSystem&& other) noexcept = default;
		ILightSystem& operator=(const ILightSystem& other) = default;
		ILightSystem& operator=(ILightSystem&& other) noexcept = default;
		virtual ~ILightSystem() = default;

		virtual void CreateLight(GE::ILight** outLight) const = 0;
		virtual void RegisterLight(GE::ILight* light) const = 0;
		virtual void UnRegisterLight(GE::ILight* light) const = 0;
	};

	class LightSystem final : public ILightSystem
	{
	public:
		LightSystem() = default;

		void Initialize(GE::ILightSystem* lightSystem);
		void Finalize();

		void CreateLight(GE::ILight** outLight) const override;
		void RegisterLight(GE::ILight* light) const override;
		void UnRegisterLight(GE::ILight* light) const override;

	private:
		GE::ILightSystem* _lightSystem;
	};
}