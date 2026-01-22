#pragma once

namespace Engine::Graphics
{
	struct ICamera
	{
		ICamera() = default;
		ICamera(const ICamera& other) = default;
		ICamera(ICamera&& other) noexcept = default;
		ICamera& operator=(const ICamera& other) = default;
		ICamera& operator=(ICamera&& other) noexcept = default;
		virtual ~ICamera() = default;
	};

	struct Camera : ICamera
	{
		virtual void SetPerspective(float nearZ, float farZ, float aspectRatio, float fov) = 0;
		virtual void SetPosition(float x, float y, float z) = 0;
		virtual void SetRotationFromAngle(float x, float y, float z) = 0;
		virtual void SetRotationFromRadian(float x, float y, float z) = 0;

		virtual void Finalize() = 0;
	};
}
