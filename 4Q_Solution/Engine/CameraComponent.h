#pragma once

namespace Engine::Component
{
	class CameraComponent :	public Component
	{
	public:
		explicit CameraComponent(std::wstring name, float nearZ, float farZ, SIZE size, float fov);

		void Setup(Modules modules) override;
		void Initialize() override;
		void Attach() override;
		void Detach() override;
		void Finalize() override;

		void Activate() const;

		void SetPosition(Math::Vector3 position);
		void SetRotation(Math::Vector3 rotation);

		void Rotate(Math::Vector3 rotation);

	private:
		std::wstring _name;

		float _nearZ;
		float _farZ;
		SIZE _size;
		float _fov;

		GEGraphics::Manager* _graphicsManager;
		Graphics::Camera* _camera;
	};
}

