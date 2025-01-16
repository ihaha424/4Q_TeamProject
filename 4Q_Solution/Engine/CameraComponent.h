#pragma once

namespace Engine::Component
{
	class CameraComponent :
		public Component
	{
	public:
		explicit CameraComponent(std::wstring name, float nearZ, float farZ, SIZE size, float fov);

		void Initialize() override;
		void Attach() override;
		void Detach() override;
		void Finalize() override;

		void Activate() const;

	private:
		std::wstring _name;

		float _nearZ;
		float _farZ;
		SIZE _size;
		float _fov;

		GE::ICamera* _camera;
	};
}

