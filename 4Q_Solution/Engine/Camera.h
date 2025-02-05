#pragma once

namespace Engine::Component
{
	class Camera :	public Component
	{
	public:
		explicit Camera(float nearZ, float farZ, Math::Size size, float fov);

		void SetName(std::wstring&& name);

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Detach() override;
		void Finalize() override;

		void Activate() const;

		Engine::Math::Matrix GetCameraMatrix() const;
		void SetPosition(Math::Vector3 position) const;
		void SetRotation(Math::Vector3 rotation) const;
		void SetParent(Math::Matrix* matrix) const;
		Engine::Math::Vector3 Forward() const;

		void Rotate(Math::Vector3 rotation);

	private:
		std::wstring _name = L"";

		float _nearZ;
		float _farZ;
		Math::Size _size;
		float _fov;

		GEGraphics::Manager* _graphicsManager;
		//Graphics::Camera* _camera;
		GE::ICamera* _geCamera;
	};
}

