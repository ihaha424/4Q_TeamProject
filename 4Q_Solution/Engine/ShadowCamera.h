#pragma once

namespace Engine::Component
{
	class ShadowCamera : public Camera
	{
	public:
		explicit ShadowCamera(float nearZ, float farZ, Math::Size size, float fov);

	public:
		void Activate() const;
	};
}