#pragma once

namespace Engine::Component
{
	class Camera;
	class FixedArm : public Component
	{
	public:
		FixedArm();

		void SetDistance(float distance);
		void SetTarget(Transform* target);
		void SetCameraComponent(Camera* camera);

		void Initialize(const Modules& modules) override;

		void Update(float deltaTime) override;

		void Rotate(const Math::Vector3& value);

		void SetCameraPosition(const Math::Vector2& value);

		Math::Vector3 GetForward() const;

	private:
		Transform* _target;
		Camera* _camera;

		float _distance;

		Math::Vector3 _rotation;
		Math::Vector2 _cameraPosition;
		Math::Matrix _matrix;
	};
}
