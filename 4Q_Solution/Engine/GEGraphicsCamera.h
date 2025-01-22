#pragma once

namespace Engine::GEGraphics
{
	class Camera final : public Graphics::Camera
	{
	public:
		Camera();

		void Setup(GE::ICamera* camera);

		void Finalize() override;

		void SetPerspective(float nearZ, float farZ, float aspectRatio, float fov) override;
		void SetPosition(float x, float y, float z) override;
		void SetRotationFromAngle(float x, float y, float z) override;
		void SetRotationFromRadian(float x, float y, float z) override;

		[[nodiscard]] GE::ICamera* Get() const;

	private:
		GE::ICamera* _camera;
	};
}
